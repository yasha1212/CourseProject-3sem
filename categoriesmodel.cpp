#include "categoriesmodel.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QVariant>
#include <QMessageBox>

CategoriesModel::CategoriesModel()
{
}

bool isUnique(QString id, QString table)
{
    QSqlQuery query(QSqlDatabase::database(table + "_connection"));
    query.exec("SELECT id FROM " + table);
    while(query.next())
        if(query.value(0).toString() == id)
            return false;
    return true;
}

bool CategoriesModel::addCurrency(QString id, double fromCoeff, double toCoeff)
{
    if(id.count() != 0)
    {
        if(isUnique(id, "currencies"))
        {
            if(fromCoeff != 0 && toCoeff != 0)
            {
                QSqlQuery query(QSqlDatabase::database("currencies_connection"));
                query.prepare("INSERT INTO currencies(id, fromUSD, toUSD, isMain)"
                              "VALUES(:id, :fromUSD, :toUSD, :isMain)");
                query.bindValue(":id", id);
                query.bindValue(":fromUSD", QString::number(fromCoeff, 'f', 4));
                query.bindValue(":toUSD", QString::number(toCoeff, 'f', 4));
                query.bindValue(":isMain", "no");
                query.exec();
                return true;
            }
            else
                QMessageBox::warning(0, APP_NAME, "Coefficients can not be 0!");
        }
        else
            QMessageBox::warning(0, APP_NAME, "Name must be unique!");
    }
    else
        QMessageBox::warning(0, APP_NAME, "Name field must be filled!");
    return false;
}

bool CategoriesModel::addCategory(QString id)
{
    if(id.count() != 0)
    {
        if(isUnique(id, "categories"))
        {
            QSqlQuery query(QSqlDatabase::database("categories_connection"));
            query.prepare("INSERT INTO categories(id)"
                          "VALUES(:id)");
            query.bindValue(":id", id);
            query.exec();
            return true;
        }
        else
            QMessageBox::warning(0, APP_NAME, "Name of the new category must be unique!");
    }
    else
        QMessageBox::warning(0, APP_NAME, "Name field must be filled!");
    return false;
}
