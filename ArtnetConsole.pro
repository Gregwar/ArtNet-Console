#-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T23:23:53
#
#-------------------------------------------------

QT       += core gui

TARGET = ArtnetConsole
TEMPLATE = app


SOURCES += main.cpp\
        artnetconsole.cpp \
    consolechannel.cpp \
    artnetmanager.cpp

HEADERS  += artnetconsole.h \
    consolechannel.h \
    artnetmanager.h

FORMS    += artnetconsole.ui \
    consolechannel.ui

LIBS += -lartnet

RESOURCES += \
    images.qrc

OTHER_FILES += \
    style.css
