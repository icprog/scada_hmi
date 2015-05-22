#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "hmi_client.h"
#include "widgets/sensorwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, HMI_Client* hmi = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    HMI_Client* hmi;
private slots:
    void onConnectClicked();
    void onStartHMI_Clicked();
    void onServerConnected();
    void onServerConnectionFailed(QAbstractSocket::SocketError error);
    void onServerDisconnected();
    void onDeviceListChange(DeviceInterface*dev);

    void on_actionDisconnect_triggered();
};

#endif // MAINWINDOW_H
