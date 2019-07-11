#-------------------------------------------------
#
# Project created by QtCreator 2019-06-28T12:20:56
#
#-------------------------------------------------

QT       += core
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += network

TARGET = SignalGenerator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += console

SOURCES += \
        client.cpp \
        configreader.cpp \
        controller.cpp \
        datadebugger.cpp \
        framecreator.cpp \
        frameparser.cpp \
        main.cpp \
        oscillator.cpp \
        sinusoscillator.cpp \
        tcpclient.cpp \
        udpclient.cpp

HEADERS += \
        channelattributes.h \
        client.h \
        configreader.h \
        controller.h \
        datadebugger.h \
        frame.h \
        framecreator.h \
        frameparser.h \
        oscillator.h \
        sinusoscillator.h \
        tcpclient.h \
        udpclient.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
