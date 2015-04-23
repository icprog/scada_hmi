#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, HMI_Client* hmi)  :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->hmi = hmi;
    ui->setupUi(this);
    connect(this->hmi, SIGNAL(connectedToServer()), this, SLOT(onServerConnected()));
    connect(this->hmi, SIGNAL(connectionFailed(QAbstractSocket::SocketError)), this, SLOT(onServerConnectionFailed(QAbstractSocket::SocketError)));
    connect(this->hmi, SIGNAL(disconnectedFromServer()), this, SLOT(onServerDisconnected()));
    connect(this->hmi, SIGNAL(deviceListChanged(DeviceInterface*)), this, SLOT(onDeviceListChange(DeviceInterface*)));

    QIntValidator* validator = new QIntValidator(0,65535);
    ui->hostAddressEdit->setValidator(validator);
    connect(this->ui->connectButton, SIGNAL(clicked(), this, SLOT(onConnectClicked()));
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
}
