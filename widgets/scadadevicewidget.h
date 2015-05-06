#ifndef SCADADEVICEWIDGET_H
#define SCADADEVICEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "common/scadadevice.h"
#include "deviceinterface.h"

class ScadaDeviceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScadaDeviceWidget(QWidget *parent = 0/*, ScadaDeviceInterface *device = 0*/);
//    ScadaDeviceWidget(QWidget *parent);
    ~ScadaDeviceWidget();

protected:
    QLabel* nameLabel;
    QLabel* briefLabel;

    QPushButton* powerSwitchButton;
    QPushButton* sendButton;

//    DeviceInterface* device;

signals:
    void powerSwitchClicked(DeviceInterface* device, bool state);
public slots:
    virtual void onRealTimeDataUpdate() = 0;
};

#endif // SCADADEVICEWIDGET_H
