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

void MainWinModel::setCurrency(QString currency)
{
    this->currency = currency;
}

QString MainWinModel::getCurrency()
{
    return this->currency;
}

