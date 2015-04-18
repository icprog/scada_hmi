#ifndef HMI_CLIENT_H
#define HMI_CLIENT_H
#include <QObject>
#include <QTcpSocket>

class HMI_Client : public QObject
{
    Q_OBJECT
public:
    HMI_Client();
    ~HMI_Client();
    bool connectToServer();
    bool disconnect();

    QList<ScadaDevice*>* getDeviceList();

    ScadaDevice* findDevice(int uuid);

private:
    QTcpSocket *socket;
    QList<ScadaDevice*> deviceList;
//    HumanMachineInterface* hmi;

public slots:
    void onConnected();
    void onDisconnected();

private slots:
    void onDataReceived();
signals:
    void deviceListChanged(DeviceInterface* device); //for UI to handle new devices


};

#endif // HMI_CLIENT_H
