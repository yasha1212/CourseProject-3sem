#include "mainwindow.h"
#include <QApplication>
#include "QtSql/QSqlDatabase"
#include <QMessageBox>
#include <QSqlQuery>

bool createConnection(QString id)
{
    QSqlDatabase db;
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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    createConnection("wallets");
    createConnection("transactions");
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("CREATE table wallets"
               "(id text,"
               "date text,"
               "currency text,"
               "value text)");
    QSqlQuery secondQuery(QSqlDatabase::database("transactions_connection"));
    secondQuery.exec("CREATE TABLE transactions"
               "(id text,"
               "type text,"
               "value text,"
               "currency text,"
               "date text,"
               "category text)");
    MainWindow w;
    w.show();
    return a.exec();
}
