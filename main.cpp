#include "mainwindow.h"
#include <QApplication>
#include "hmi_client.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HMI_Client client;
    MainWindow w(0, &client);
    w.show();

    return a.exec();
}
