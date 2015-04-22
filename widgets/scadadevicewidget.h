#ifndef SCADADEVICEWIDGET_H
#define SCADADEVICEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "common/scadadevice.h"

class ScadaDeviceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScadaDeviceWidget(QWidget *parent = 0/*, ScadaDeviceInterface *device = 0*/);
    ~ScadaDeviceWidget();

protected:
    QLabel* nameLabel;
    QLabel* briefLabel;

    QPushButton* powerSwitchButton;
    QPushButton* sendButton;

//    ScadaDeviceInterface* device;

signals:

public slots:
};

#endif // SCADADEVICEWIDGET_H
