#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "widgets/scadadevicewidget.h"
#include "widgets/qcustomplot.h"
#include "sensorinterface.h"

class SensorWidget : public ScadaDeviceWidget
{
    Q_OBJECT
public:
    SensorWidget(QWidget *parent, SensorInterface* sensor);
    ~SensorWidget();
private:
    SensorInterface* device;
    QCustomPlot *plot;
    QLabel* currentValueIndicator;
    QLabel* rangeBrief;

    QVBoxLayout* panelLayout;
    QHBoxLayout* mainLayout;

    void plotSetup();
    void plotUpdate();

public slots:
    void onPowerButtonClicked();
    void onRealTimeDataUpdate();

};

#endif // SENSORWIDGET_H
