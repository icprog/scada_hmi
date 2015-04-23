#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hmi_client.h"

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
    void onServerConnected();
    void onServerConnectionFailed();

};

#endif // MAINWINDOW_H