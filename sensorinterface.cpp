#include "sensorinterface.h"

SensorInterface::SensorInterface(QObject *parent) : QObject(parent)
{

}

SensorInterface::~SensorInterface()
{

}

QString SensorInterface::getDeviceName()
{
    return name;
}

QString SensorInterface::getDeviceBrief()
{
    return factoryData;
}

int SensorInterface::getDeviceState()
{
    return (int)deviceState;
}

int SensorInterface::getUUID()
{
    return uuid;
}

QString SensorInterface::getMeasurandName()
{
    return measurandName;
}

QString SensorInterface::getMeasurandUnit()
{
    return measurandUnit;
}

double SensorInterface::getRangeMax()
{
    return rangeMax;
}

double SensorInterface::getRangeMin()
{
    return rangeMin;
}

 double SensorInterface::getCurrentValue()
 {
     return currentValue;
 }

bool SensorInterface::dataReceived(Packet* data)
{
    Sensor::dataReceived(data);
    emit dataUpdate();
}

void SensorInterface::setDeviceState(bool state)
{
    if(state)
        this->deviceState = STATE_ON;
    else this->deviceState = STATE_OFF;
}
