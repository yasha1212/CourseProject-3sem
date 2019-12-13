#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QString>

class DBConnection
{
public:
    DBConnection();
    bool createConnection(QString id);
    void configureTables();
};

#endif // DBCONNECTION_H
