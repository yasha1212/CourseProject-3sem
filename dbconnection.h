#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QString>
#include <QSqlDatabase>

class DBConnection
{
public:
    DBConnection();
    bool createConnection(QString id);
    void configureTables();
private:
    QSqlDatabase db;
};

#endif // DBCONNECTION_H
