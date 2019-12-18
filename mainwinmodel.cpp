#include "mainwinmodel.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QMessageBox>
#include <sstream>
#include <QStringListModel>
#include <cmath>

MainWinModel::MainWinModel()
{
}

double MainWinModel::convertToMainCurrency(double value, QString walletCurrency)
{
    QSqlQuery query(QSqlDatabase::database("currencies_connection"));
    double toCoeff, fromCoeff;
    query.prepare("SELECT toUSD FROM currencies WHERE id = ?");
    query.addBindValue(walletCurrency);
    query.exec();
    while(query.next())
    {
        toCoeff = query.value(0).toDouble();
        query.prepare("SELECT fromUSD FROM currencies WHERE id = ?");
        query.addBindValue(currency);
        query.exec();
        while(query.next())
        {
            fromCoeff = query.value(0).toDouble();
            return round(value * toCoeff * fromCoeff * 100) / 100;
        }
    }
}

double MainWinModel::getSum()
{
    double sum = 0;
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT id, date, inclusion, currency, value FROM wallets");
    while(query.next())
        if(query.value(2) == "yes")
            sum += convertToMainCurrency(query.value(4).toDouble(), query.value(3).toString());
    return sum;
}

QStringList MainWinModel::getWalletsList()
{
    QStringList sList;
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT id, date, inclusion, currency, value FROM wallets");
    while(query.next())
        sList.append(query.value(0).toString());
    return sList;
}

bool MainWinModel::isReadyForAdding()
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT COUNT(*) FROM wallets");
    int rows = 0;
    if(query.next())
        rows = query.value(0).toInt();
    if(rows < 12)
    {
        return true;
    }
    else
    {
        QMessageBox::warning(0, APP_NAME, "Maximal amount of wallets is 12!");
        return false;
    }
}

void MainWinModel::setCurrency()
{
    QString currency;
    QSqlQuery query(QSqlDatabase::database("currencies_connection"));
    query.prepare("SELECT id FROM currencies WHERE isMain = ?");
    query.addBindValue("yes");
    query.exec();
    while(query.next())
        currency = query.value(0).toString();
    this->currency = currency;
}

QString MainWinModel::getCurrency()
{
    return this->currency;
}

