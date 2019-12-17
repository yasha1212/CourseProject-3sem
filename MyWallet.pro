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
    newwalletwindow.cpp \
    walletwindow.cpp \
    incomewindow.cpp \
    dbconnection.cpp \
    mainwinmodel.cpp \
    newwalletwinmodel.cpp \
    walletwinmodel.cpp \
    incomewinmodel.cpp \
    walletsettingswindow.cpp \
    walletsettingswinmodel.cpp

HEADERS  += mainwindow.h \
    newwalletwindow.h \
    walletwindow.h \
    incomewindow.h \
    dbconnection.h \
    mainwinmodel.h \
    newwalletwinmodel.h \
    walletwinmodel.h \
    incomewinmodel.h \
    walletsettingswindow.h \
    walletsettingswinmodel.h

FORMS    += mainwindow.ui \
    newwalletwindow.ui \
    walletwindow.ui \
    incomewindow.ui \
    walletsettingswindow.ui

RESOURCES += \
    images.qrc
