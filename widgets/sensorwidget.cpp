#include "sensorwidget.h"

SensorWidget::SensorWidget(QWidget* parent) : ScadaDeviceWidget(parent)
{
    plot = new QCustomPlot();
    panelLayout = new QVBoxLayout();
    mainLayout = new QHBoxLayout();


    panelLayout->addWidget(nameLabel);
    panelLayout->addWidget(briefLabel);
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
