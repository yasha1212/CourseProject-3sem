#include "settingswinmodel.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QVariant>

SettingsWinModel::SettingsWinModel()
{
}

QStringList SettingsWinModel::getCurrencies()
{
    QStringList list;
    QSqlQuery query(QSqlDatabase::database("currencies_connection"));
    query.exec("SELECT id FROM currencies");
    while(query.next())
        list.append(query.value(0).toString());
    return list;
}

void SettingsWinModel::setMainCurrency(QString currency)
{
    QSqlQuery query(QSqlDatabase::database("currencies_connection"));
    query.prepare("UPDATE currencies SET isMain = ?");
    query.addBindValue("no");
    query.exec();
    query.prepare("UPDATE currencies SET isMain = ? WHERE id = ?");
    query.addBindValue("yes");
    query.addBindValue(currency);
    query.exec();
}
