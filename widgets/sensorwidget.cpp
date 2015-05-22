#include "sensorwidget.h"

SensorWidget::SensorWidget(QWidget* parent, SensorInterface* sensor) : ScadaDeviceWidget(parent)
{
    plot = new QCustomPlot();
    panelLayout = new QVBoxLayout();
    mainLayout = new QHBoxLayout();
    currentValueIndicator = new QLabel();
    rangeBrief = new QLabel();
    this->device = sensor;
    connect(this->device, SIGNAL(dataUpdate()), this, SLOT(onRealTimeDataUpdate()));
    connect(this->powerSwitchButton, SIGNAL(clicked()), this, SLOT(onPowerButtonClicked()));

    panelLayout->addWidget(nameLabel);
    panelLayout->addWidget(briefLabel);
    panelLayout->addWidget(rangeBrief);
    panelLayout->addWidget(currentValueIndicator);
    panelLayout->addStretch();
    panelLayout->addWidget(powerSwitchButton);
    this->sendButton->setVisible(false);
    mainLayout->addLayout(panelLayout,2);
    mainLayout->addStretch(1);
    mainLayout->addWidget(plot,5);

    delete this->layout();
    this->setLayout(mainLayout);
    plotSetup();
    this->nameLabel->setText(device->getDeviceName());
    this->briefLabel->setText(device->getDeviceBrief());
    this->rangeBrief->setText("Measure range: " +
                              QString::number(device->getRangeMin()) +
                              " - " +
                              QString::number(device->getRangeMax()) +
                              " " +
                              device->getMeasurandUnit());
}

SensorWidget::~SensorWidget()
{

}



void SensorWidget::onPowerButtonClicked()
{
    if(device->getDeviceState()==STATE_OFF)
        emit powerSwitchClicked(device, true);
    else
        emit powerSwitchClicked(device, false);
}

void SensorWidget::onRealTimeDataUpdate()
{
    //plot data
    this->currentValueIndicator->setText(QString::number(device->getCurrentValue()) + " " + device->getMeasurandUnit());
    plotUpdate();
}

void SensorWidget::plotSetup()
{
    plot->addGraph();
    plot->graph(0)->setPen(QPen(Qt::blue));
    plot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    plot->graph(0)->setAntialiasedFill(false);

    plot->yAxis->setLabel(device->getMeasurandName() + "[" + device->getMeasurandUnit() + "]");
//    plot->yAxis->setRangeLower(device->getRangeMin());
//    plot->yAxis->setRangeUpper(device->getRangeMax());
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
      double data = device->getCurrentValue();
      plot->graph(0)->addData(key, data);


      // remove data of lines that's outside visible range:
      plot->graph(0)->removeDataBefore(key-8);
      plot->yAxis->rescale();

      lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    plot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    plot->replot();


}


