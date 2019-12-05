#include "mainwindow.h"
#include <QApplication>
#include "QtSql/QSqlDatabase"
#include <QMessageBox>

bool createConnection()
{
    QSqlDatabase db;
    if(!(db.contains("qt_sql_default_connection")))
        db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("wallets.sqlite");
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
    createConnection();
    MainWindow w;
    w.show();
    return a.exec();
}
