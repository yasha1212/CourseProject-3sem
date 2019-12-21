#-------------------------------------------------
#
# Project created by QtCreator 2019-11-15T11:54:27
#
#-------------------------------------------------

QT       += core gui sql charts

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
    walletsettingswinmodel.cpp \
    settingswindow.cpp \
    settingswinmodel.cpp \
    currencieswindow.cpp \
    categorieswindow.cpp \
    categoriesmodel.cpp \
    statwindow.cpp \
    statwinmodel.cpp

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
    walletsettingswinmodel.h \
    settingswindow.h \
    settingswinmodel.h \
    currencieswindow.h \
    categorieswindow.h \
    categoriesmodel.h \
    statwindow.h \
    statwinmodel.h

FORMS    += mainwindow.ui \
    newwalletwindow.ui \
    walletwindow.ui \
    incomewindow.ui \
    walletsettingswindow.ui \
    settingswindow.ui \
    currencieswindow.ui \
    categorieswindow.ui \
    statwindow.ui

RESOURCES += \
    images.qrc
