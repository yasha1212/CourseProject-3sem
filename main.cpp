#include "mainwindow.h"
#include <QApplication>
#include "dbconnection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBConnection *model = new DBConnection;

    model->createConnection("wallets");
    model->createConnection("transactions");
    model->createConnection("currencies");
    model->configureTables();

    MainWindow w;
    w.show();
    return a.exec();
}
