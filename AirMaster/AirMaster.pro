#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T20:59:17
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AirMaster
TEMPLATE = app
LIBS += /usr/local/Cellar/hiredis/0.13.3/lib/libhiredis.a

INCLUDEPATH +=/usr/local/include/
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
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
    airconditionmaster.cpp \
    loginairmaster.cpp \
    airencrypter.cpp \
    airpacket.cpp \
    aircommon.cpp \
    requeuehelper.cpp \
    tcppipetoservant.cpp \
    packethandler.cpp \
    resqueuehandler.cpp \
    airdatabase.cpp \
    aireportsystem.cpp \
    airfee.cpp \
    logindialog.cpp \
    reportwidget.cpp

HEADERS += \
        mainwindow.h \
    airconditionmaster.h \
    loginairmaster.h \
    airencrypter.h \
    json.hpp \
    airpacket.h \
    aircommon.h \
    requeuehelper.h \
    tcppipetoservant.h \
    packethandler.h \
    resqueuehandler.h \
    airdatabase.h \
    aireportsystem.h \
    airfee.h \
    logindialog.h \
    reportwidget.h

FORMS += \
        mainwindow.ui \
    logindialog.ui \
    reportwidget.ui

DISTFILES += \
    database_design.org
