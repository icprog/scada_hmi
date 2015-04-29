#ifndef SENSORINTERFACE_H
#define SENSORINTERFACE_H

#include "common/sensor.h"
#include "common/packet.h"
#include "deviceinterface.h"


class SensorInterface : public Sensor, public DeviceInterface
{
    
public:
    SensorInterface();
    ~SensorInterface();
    QString getDeviceName();
    QString getDeviceBrief();
    int getDeviceState();
    int getUUID();
    QString getMeasurandName();
    QString getMeasurandUnit();
    double getRangeMax();
    double getRangeMin();

    double getCurrentValue();

    bool dataReceived(Packet* data);

};

#endif // SENSORINTERFACE_H
