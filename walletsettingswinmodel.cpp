#include "walletsettingswinmodel.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include <cmath>

WalletSettingsWinModel::WalletSettingsWinModel()
{
}

QStringList WalletSettingsWinModel::getCurrenciesList()
{
    QStringList list;
    QSqlQuery query(QSqlDatabase::database("currencies_connection"));
    query.exec("SELECT id FROM currencies");
    while(query.next())
    {
        list.append(query.value(0).toString());
    }
    return list;
}

void WalletSettingsWinModel::setInclusion(QString inclusion)
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.prepare("UPDATE wallets SET inclusion = :inclusion WHERE id = :id");
    query.bindValue(":inclusion", inclusion);
    query.bindValue(":id", name);
    query.exec();
}

double WalletSettingsWinModel::convertCurrency(double value, QString walletCurrency, QString newCurrency)
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
        query.addBindValue(newCurrency);
        query.exec();
        while(query.next())
        {
            fromCoeff = query.value(0).toDouble();
            return round(value * toCoeff * fromCoeff * 100) / 100;
        }
    }
}

bool WalletSettingsWinModel::isCorrectName(QString name)
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT id FROM wallets");
    while(query.next())
        if(query.value(0) == name)
            return false;
    return true;
}

void WalletSettingsWinModel::setCurrency(QString currency)
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    double initialValue, newValue;
    QString initialCurrency;
    query.prepare("SELECT value, currency FROM wallets WHERE id = :id");
    query.bindValue(":id", name);
    query.exec();
    while(query.next())
    {
        initialValue = query.value(0).toDouble();
        initialCurrency = query.value(1).toString();
    }
    newValue = convertCurrency(initialValue, initialCurrency, currency);
    query.prepare("UPDATE wallets SET value = :value, currency = :currency WHERE id = :id");
    query.bindValue(":id", name);
    query.bindValue(":value", QString::number(newValue, 'f', 2));
    query.bindValue(":currency", currency);
    query.exec();
}

void WalletSettingsWinModel::setName(QString newName)
{
    if(newName.count() != 0)
    {
        if(isCorrectName(newName))
        {
            QSqlQuery query(QSqlDatabase::database("wallets_connection"));
            QSqlQuery queryTransactions(QSqlDatabase::database("transactions_connection"));
            query.prepare("UPDATE wallets SET id = ? WHERE id = ?");
            query.addBindValue(newName);
            query.addBindValue(name);
            query.exec();
            queryTransactions.prepare("UPDATE transactions SET id = ? WHERE id = ?");
            queryTransactions.addBindValue(newName);
            queryTransactions.addBindValue(name);
            queryTransactions.exec();
        }
        else
            QMessageBox::warning(0, APP_NAME, "Name must be a unique identifier!");
    }
    else
        QMessageBox::warning(0, APP_NAME, "Name field must be filled!");
}
