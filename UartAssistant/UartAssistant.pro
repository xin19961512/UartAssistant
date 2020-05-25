#-------------------------------------------------
#
# Project created by QtCreator 2020-05-14T14:32:11
#
#-------------------------------------------------

QT       += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UartAssistant
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dlgcom.cpp \
    Qextserial/qextserialbase.cpp \
    Qextserial/win_qextserialport.cpp \
    User/uartbase.cpp \
    dlgabout.cpp

HEADERS += \
        mainwindow.h \
    dlgcom.h \
    Qextserial/qextserialbase.h \
    Qextserial/win_qextserialport.h \
    User/uartbase.h \
    dlgabout.h

FORMS += \
        mainwindow.ui \
    dlgcom.ui \
    dlgabout.ui

RC_FILE = UartAssistant.rc

QMAKE_CXXFLAGS +=  -Wno-unused-parameter
QMAKE_CXXFLAGS +=  -Wno-unused-variable

RESOURCES += \
    rc.qrc
