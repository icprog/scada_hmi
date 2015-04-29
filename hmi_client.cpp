#include "hmi_client.h"

HMI_Client::HMI_Client()
{
    this->hmi = new HumanMachineInterface();
    this->deviceList = new QList<DeviceInterface*>;
    this->socket = new QTcpSocket(this);
}

HMI_Client::~HMI_Client()
{
    delete hmi;
    delete deviceList;
}

void HMI_Client::connectToServer(QString hostName, int portNumber)
{
    socket->connectToHost(hostName, portNumber);
    connect(this->socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(this->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

bool HMI_Client::disconnect()
{
    socket->disconnectFromHost();
    return true;
}

void HMI_Client::onConnected()
{
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(onDataReceived()));
    emit connectedToServer();
    socket->write(hmi->getInitPacket().encode());
}

void HMI_Client::onSocketError(QAbstractSocket::SocketError error)
{
    emit connectionFailed(error);
}

void HMI_Client::onDisconnected()
{
    emit disconnectedFromServer();
}

void HMI_Client::onDataReceived()
{
    QByteArray rxData = socket->readAll();
    Packet packet;
    QList<Packet> packetList;
    while(packet.decode(&rxData)) //there can be more packets which came together
    {
        packetList.append(packet); //we will separate them and put into list
    }
    foreach(Packet packet, packetList)
    {
        if(packet.getPacketType()==Packet::SENSOR_INIT ||   //if piece of device list received
                packet.getPacketType()==Packet::REGULATOR_INIT)
        {
            //TODO: avoid adding the same dev twice
            DeviceInterface* device;
            if(packet.getPacketType()==Packet::SENSOR_INIT)
            {
                device = new SensorInterface();
                ScadaDevice* scadaDev = dynamic_cast<ScadaDevice*>(device);
                if(scadaDev->initReceived(&packet))
                {
                    deviceList->append(device);
                    emit deviceListChanged(device);
                }
                else delete device;
            }
//            else device = new RegulatorInterface()





        }
        
        if(packet.getPacketType()==Packet::DATA)
        {
//            hmi->dataReceived(&packet);
            ScadaDevice* dev = findDevice(packet.getDeviceID());
            if(dev)
            {
                dev->dataReceived(&packet);
            }
        }
    }
}

QList<DeviceInterface*>* HMI_Client::getDeviceList()
{
    return deviceList;
}

ScadaDevice* HMI_Client::findDevice(int uuid)
{
    for(int i = 0; i<deviceList->size(); i++)
    {
        ScadaDevice *device = dynamic_cast<ScadaDevice*>(deviceList->at(i));
        if(device->getUUID()==uuid)
        {
            return device;
        }
    }
    return NULL;
}

void HMI_Client::appendToWishList(ScadaDevice* device)
{
    this->hmi->appendToWishlist(device);
}

void HMI_Client::sendWishlist()
{
    socket->write(hmi->getSettingsPacket().encode());
}
