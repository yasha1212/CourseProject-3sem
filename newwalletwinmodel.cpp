#include "newwalletwinmodel.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QMessageBox>
#include <QDateTime>
#include <QLocale>

NewWalletWinModel::NewWalletWinModel()
{
}

QStringList NewWalletWinModel::getCurrenciesList()
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

bool NewWalletWinModel::isCorrectName(QString name)
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT id FROM wallets");
    while(query.next())
        if(query.value(0) == name)
            return false;
    return true;
}

bool NewWalletWinModel::addWallet(QString name, QString currency, QString inclusion, double value)
{
    if(name.count() != 0)
    {
        if(isCorrectName(name))
        {
            if(currency.count() != 0)
            {
                if(inclusion.count() != 0)
                {
                    inclusion = inclusion == "Include in total"? "yes": "no";
                    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
                    query.prepare("INSERT INTO wallets (id, date, inclusion, currency, value)"
                                  "VALUES (:id, :date, :inclusion, :currency, :value)");
                    query.bindValue(":id", name);
                    QString dateTime = QLocale{QLocale::English}.toString(QDateTime::currentDateTime(), DATE_FORMAT);
                    query.bindValue(":date", dateTime);
                    query.bindValue(":inclusion", inclusion);
                    query.bindValue(":currency", currency);
                    QString sign = value < 0? "": "+";
                    query.bindValue(":value", sign + QString::number(value, 'f', 2));
                    query.exec();
                    return true;
                }
                else
                    QMessageBox::warning(0, APP_NAME, "Inclusion option must be selected!");
            }
            else
                QMessageBox::warning(0, APP_NAME, "Currency must be selected!");
        }
        else
            QMessageBox::warning(0, APP_NAME, "Such identifier is already exists!");
    }
    else
        QMessageBox::warning(0, APP_NAME, "Name field must be filled!");
    return false;
}
