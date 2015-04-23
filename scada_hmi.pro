#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T22:30:01
#
#-------------------------------------------------

QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scada_hmi
TEMPLATE = app


SOURCES += main.cpp\
    hmi_client.cpp \
    widgets/qcustomplot.cpp \
    widgets/scadadevicewidget.cpp \
    widgets/sensorwidget.cpp \
    common/humanmachineinterface.cpp \
    common/packet.cpp \
    common/scadadevice.cpp \
    common/sensor.cpp \
    deviceinterface.cpp \
    sensorinterface.cpp \
    mainwindow.cpp

HEADERS  += \
    hmi_client.h \
    widgets/qcustomplot.h \
    widgets/scadadevicewidget.h \
    widgets/sensorwidget.h \
    common/humanmachineinterface.h \
    common/packet.h \
    common/scadadevice.h \
    common/sensor.h \
    deviceinterface.h \
    sensorinterface.h \
    mainwindow.h

FORMS    += \
    mainwindow.ui
