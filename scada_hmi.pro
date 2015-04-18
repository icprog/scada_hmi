#-------------------------------------------------
#
# Project created by QtCreator 2015-04-17T22:30:01
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scada_hmi
TEMPLATE = app


SOURCES += main.cpp\
        connectwindow.cpp \
    hmi_client.cpp \
    widgets/qcustomplot.cpp \
    widgets/scadadevicewidget.cpp \
    widgets/sensorwidget.cpp

HEADERS  += connectwindow.h \
    hmi_client.h \
    widgets/qcustomplot.h \
    widgets/scadadevicewidget.h \
    widgets/sensorwidget.h

FORMS    += connectwindow.ui
