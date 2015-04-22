#ifndef HMI_CLIENT_H
#define HMI_CLIENT_H
#include <QObject>
#include <QTcpSocket>
#include "common/scadadevice.h"
#include "common/humanmachineinterface.h"
#include "common/packet.h"
#include "deviceinterface.h"
#include "sensorinterface.h"

class HMI_Client : public QObject
{
    Q_OBJECT
public:
    HMI_Client();
    ~HMI_Client();
    bool connectToServer(QString hostName, int portNumber);
    bool disconnect();

    QList<DeviceInterface*>* getDeviceList();

    ScadaDevice* findDevice(int uuid);

private:
    QTcpSocket *socket;
    HumanMachineInterface* hmi;
    QList<DeviceInterface*> *deviceList;
//    HumanMachineInterface* hmi;

public slots:
    void onConnected();
    void onDisconnected();

private slots:
    void onDataReceived();
signals:
    void deviceListChanged(DeviceInterface* device); //for UI to handle new devices
    void connectionFailed();
    void connectedToServer();
    void disconnectedFromServer();

};

#endif // HMI_CLIENT_H
