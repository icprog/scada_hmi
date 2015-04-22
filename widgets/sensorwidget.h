#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "widgets/scadadevicewidget.h"
#include "widgets/qcustomplot.h"

class SensorWidget : public ScadaDeviceWidget
{
    Q_OBJECT
public:
    SensorWidget(QWidget *parent);
    ~SensorWidget();
private:
    QCustomPlot *plot;

    QVBoxLayout* panelLayout;
    QHBoxLayout* mainLayout;

public slots:
    void onPowerButtonClicked();

};

#endif // SENSORWIDGET_H
