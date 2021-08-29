#-------------------------------------------------
#
# Project created by QtCreator 2021-08-03T10:31:22
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
RC_ICONS = icon.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project8_SmartHome
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

SOURCES += \
        main.cpp \
        loginwidget.cpp \
    jsonmanager.cpp \
    menu.cpp \
    musicplayer.cpp \
    weather.cpp \
    equipment.cpp

HEADERS += \
        loginwidget.h \
    jsonmanager.h \
    menu.h \
    musicplayer.h \
    weather.h \
    equipment.h

FORMS += \
        loginwidget.ui \
    menu.ui \
    musicplayer.ui \
    weather.ui \
    equipment.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
