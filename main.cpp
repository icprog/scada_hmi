#include "connectwindow.h"
#include <QApplication>
#include "hmi_client.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ConnectWindow w;
//    w.show();
    HMI_Client client;
    client.connectToServer("localhost", 8888);
    return a.exec();
}
