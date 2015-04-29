#include "sensorwidget.h"

SensorWidget::SensorWidget(QWidget* parent, SensorInterface* sensor) : ScadaDeviceWidget(parent, sensor)
{
    plot = new Qplot();
    panelLayout = new QVBoxLayout();
    mainLayout = new QHBoxLayout();
    currentValueIndicator = new QLabel();



    panelLayout->addWidget(nameLabel);
    panelLayout->addWidget(briefLabel);
    panelLayout->addWidget(currentValueIndicator);
    panelLayout->addStretch();
    panelLayout->addWidget(powerSwitchButton);
    this->sendButton->setVisible(false);
    mainLayout->addLayout(panelLayout,1);

    delete this->layout();
    this->setLayout(mainLayout);

}

SensorWidget::~SensorWidget()
{

}



void SensorWidget::onPowerButtonClicked()
{

}

void SensorWidget::onRealTimeDataUpdate()
{
    //plot data
    this->currentValueIndicator->setText(QString::number(device->getCurrentValue));

}

void SensorWidget::plotSetup()
{
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    plot->graph(0)->setAntialiasedFill(false);

    plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    plot->xAxis->setDateTimeFormat("hh:mm:ss");
    plot->xAxis->setAutoTickStep(false);
    plot->xAxis->setTickStep(2);
    plot->axisRect()->setupFullAxesBox();

    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));


}

void SensorWidget::plotUpdate()
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
      // add data to lines:
      ui->plot->graph(0)->addData(key, device->getCurrentValue);

      // remove data of lines that's outside visible range:
      ui->plot->graph(0)->removeDataBefore(key-8);

      // rescale value (vertical) axis to fit the current data:
      ui->plot->graph(0)->rescaleValueAxis();

      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->plot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->plot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->plot->graph(0)->data()->count()+ui->plot->graph(1)->data()->count())
            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }

}
