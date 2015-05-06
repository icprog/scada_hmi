#ifndef SENSORINTERFACE_H
#define SENSORINTERFACE_H

#include "common/sensor.h"
#include "common/packet.h"
#include "deviceinterface.h"
#include <QObject>

class SensorInterface : public QObject, public Sensor, public DeviceInterface
{
    Q_OBJECT
    
public:
    SensorInterface(QObject *parent =0);
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

    void setDeviceState(bool state);
    bool dataReceived(Packet* data);
signals:
    void dataUpdate();

};

#endif // SENSORINTERFACE_H
