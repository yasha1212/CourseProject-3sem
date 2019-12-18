#include "incomewinmodel.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QMessageBox>
#include <QLocale>

IncomeWinModel::IncomeWinModel()
{
}

bool IncomeWinModel::addTransaction(QString category, double incomeValue)
{
    if(category.count() != 0)
    {
        if(incomeValue != 0)
        {
            QSqlQuery query(QSqlDatabase::database("transactions_connection"));
            query.prepare("INSERT INTO transactions(id, type, value, currency, date, category)"
                          "VALUES (:id, :type, :value, :currency, :date, :category)");
            query.bindValue(":id", id);
            QString type = incomeValue < 0? "Consumption": "Income";
            query.bindValue(":type", type);
            QString sign = incomeValue < 0? "": "+";
            query.bindValue(":value", sign + QString::number(incomeValue, 'f', 2));
            query.bindValue(":currency", currency);
            query.bindValue(":category", category);
            QString dateTime = QLocale{QLocale::English}.toString(QDateTime::currentDateTime(), DATE_FORMAT);
            query.bindValue(":date", dateTime);
            query.exec();

            QSqlQuery queryUpdate(QSqlDatabase::database("wallets_connection"));
            queryUpdate.prepare("UPDATE wallets SET value = :value WHERE id = :id");
            queryUpdate.bindValue(":id", id);
            double oldValue = value.toDouble();
            double resultValue = oldValue + incomeValue;
            sign = resultValue < 0? "": "+";
            queryUpdate.bindValue(":value", sign + QString::number(resultValue, 'f', 2));
            queryUpdate.exec();
            return true;
        }
        else
            QMessageBox::warning(0, APP_NAME, "Value field must be filled!");
    }
    else
        QMessageBox::warning(0, APP_NAME, "Category must be selected!");
    return false;
}

void IncomeWinModel::setParameters(QString currency, QString id, QString value)
{
    this->value = value;
    this->id = id;
    this->currency = currency;
}

QStringList IncomeWinModel::getCategories()
{
    QStringList list;
    QSqlQuery query(QSqlDatabase::database("categories_connection"));
    query.exec("SELECT id FROM categories");
    while(query.next())
        list.append(query.value(0).toString());
    return list;
}
