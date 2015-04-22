#include "scadadevicewidget.h"

ScadaDeviceWidget::ScadaDeviceWidget(QWidget *parent) : QWidget(parent)
{
    nameLabel = new QLabel("name", this);
    QFont f( "Arial", 15, QFont::Bold);
    nameLabel->setFont(f);
    briefLabel = new QLabel("brief", this);

    powerSwitchButton = new QPushButton("On/Off", this);
    sendButton = new QPushButton("Send", this);

//    this->device = device;
}

ScadaDeviceWidget::~ScadaDeviceWidget()
{

}

