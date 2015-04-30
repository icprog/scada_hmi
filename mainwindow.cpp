#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, HMI_Client* hmi)  :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(240,240);
    this->hmi = hmi;
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    connect(this->hmi, SIGNAL(connectedToServer()), this, SLOT(onServerConnected()));
    connect(this->hmi, SIGNAL(connectionFailed(QAbstractSocket::SocketError)), this, SLOT(onServerConnectionFailed(QAbstractSocket::SocketError)));
    connect(this->hmi, SIGNAL(disconnectedFromServer()), this, SLOT(onServerDisconnected()));
    connect(this->hmi, SIGNAL(deviceListChanged(DeviceInterface*)), this, SLOT(onDeviceListChange(DeviceInterface*)));

    QIntValidator* validator = new QIntValidator(0,65535);
    ui->deviceListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->hostAddressEdit->setValidator(validator);
    connect(this->ui->connectButton, SIGNAL(clicked()), this, SLOT(onConnectClicked()));
    connect(this->ui->startHMI_Button, SIGNAL(clicked()), this, SLOT(onStartHMI_Clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnectClicked()
{
    QString hostName = ui->hostAddressEdit->text();
    int portNumber = ui->portNumberEdit->text().toInt();
    hmi->connectToServer(hostName, portNumber);
    ui->connectButton->setEnabled(false);
    ui->connectButton->setText("Connecting...");
}

void MainWindow::onStartHMI_Clicked()
{
    QModelIndexList indexes = ui->deviceListWidget->selectionModel()->selectedIndexes();
    if(indexes.empty())
    {
        QMessageBox message;
        message.setText("Plese choose at least one device to show.");
        message.setWindowTitle("Error");
        message.exec();
        return;
    }
    foreach(QModelIndex index, indexes)
    {
        ScadaDevice *device = dynamic_cast<ScadaDevice*>(hmi->getDeviceList()->at(index.row()));
        hmi->appendToWishList(device);
        SensorInterface* sensor = dynamic_cast<SensorInterface*>(hmi->getDeviceList()->at(index.row()));
        if(sensor)
        {
            SensorWidget* widget = new SensorWidget(0, sensor);
            ui->gridLayout->addWidget(widget);
            this->setFixedSize(800,600);
        }


//        if(something else)
            
    }
    hmi->sendWishlist();

    ui->stackedWidget->setCurrentIndex(2);
   

}

void MainWindow::onServerConnected()
{
    ui->stackedWidget->setCurrentIndex(1);
    this->setFixedSize(350,550);

}
void MainWindow::onServerConnectionFailed(QAbstractSocket::SocketError error)
{
    ui->connectButton->setEnabled(true);
    ui->connectButton->setText("Connect");
    QMessageBox message;
    message.setIcon(QMessageBox::Critical);
    message.setWindowTitle("Error");
    message.setText("Connection error. Check server.");
    message.exec();
}
void MainWindow::onServerDisconnected()
{

}
void MainWindow::onDeviceListChange(DeviceInterface* dev)
{
    QString text = dev->getDeviceName() + ": " +dev->getDeviceBrief() + "(" + QString::number(dev->getUUID()) + ")";
    QListWidgetItem* item = new QListWidgetItem(text);
    ui->deviceListWidget->addItem(item);
}
