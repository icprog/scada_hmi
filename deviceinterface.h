#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H
#include <QString>
#include <QObject>
class DeviceInterface
{

public:
    DeviceInterface();
    ~DeviceInterface();
    
public:
    virtual QString getDeviceName() = 0;
    virtual QString getDeviceBrief() = 0;
    virtual int getDeviceState() = 0;
    virtual int getUUID() = 0;


};

#endif // DEVICEINTERFACE_H
