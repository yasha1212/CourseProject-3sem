#-------------------------------------------------
#
# Project created by QtCreator 2019-11-15T11:54:27
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyWallet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newwalletwindow.cpp

HEADERS  += mainwindow.h \
    newwalletwindow.h

FORMS    += mainwindow.ui \
    newwalletwindow.ui

RESOURCES += \
    images.qrc
