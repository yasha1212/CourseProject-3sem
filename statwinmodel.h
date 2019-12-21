#ifndef STATWINMODEL_H
#define STATWINMODEL_H

#include <QStringList>
#include <QtCharts>

class StatWinModel
{
public:
    StatWinModel();
    QStringList getTypes();
    QStringList getPeriods();
    QStringList getList(QString period, QString type);
    QChart *getChart(QString period, QString currPeriod, QString type, QString currency);
    double convertCurrency(double value, QString walletCurrency, QString newCurrency);
};

#endif // STATWINMODEL_H
