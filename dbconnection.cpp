#include "dbconnection.h"
#include "QtSql/QSqlDatabase"
#include <QMessageBox>
#include <QSqlQuery>

DBConnection::DBConnection()
{
}

bool DBConnection::createConnection(QString id)
{
    if(!(db.contains("qt_sql_default_connection")))
        db = QSqlDatabase::addDatabase("QSQLITE", id + "_connection");
    db.setDatabaseName(id + ".sqlite");
    if(!db.open())
    {
        QMessageBox::warning(0, "Error", "Database connecting error!");
        return false;
    }
    else return true;
}

void DBConnection::configureTables()
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("CREATE table wallets"
               "(id text,"
               "date text,"
               "inclusion text,"
               "currency text,"
               "value text)");
    QSqlQuery currenciesQuery(QSqlDatabase::database("currencies_connection"));
    currenciesQuery.exec("CREATE table currencies"
               "(id text,"
               "toUSD text,"
               "fromUSD text)");
    QSqlQuery secondQuery(QSqlDatabase::database("transactions_connection"));
    secondQuery.exec("CREATE TABLE transactions"
               "(id text,"
               "type text,"
               "value text,"
               "currency text,"
               "date text,"
               "category text)");
}
