#include "statwinmodel.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
#include <QVariant>
#include <QPieSeries>
#include <QPieSlice>
#include "cmath"

StatWinModel::StatWinModel()
{
}

QStringList StatWinModel::getTypes()
{
    QStringList list;
    list.append("Incomes");
    list.append("Consumptions");
    return list;
}

double StatWinModel::convertCurrency(double value, QString walletCurrency, QString newCurrency)
{
    QSqlQuery query(QSqlDatabase::database("currencies_connection"));
    double toCoeff, fromCoeff;
    query.prepare("SELECT toUSD FROM currencies WHERE id = ?");
    query.addBindValue(walletCurrency);
    query.exec();
    while(query.next())
    {
        toCoeff = query.value(0).toDouble();
        query.prepare("SELECT fromUSD FROM currencies WHERE id = ?");
        query.addBindValue(newCurrency);
        query.exec();
        while(query.next())
        {
            fromCoeff = query.value(0).toDouble();
            return round(value * toCoeff * fromCoeff * 100) / 100;
        }
    }
}

QChart *StatWinModel::getChart(QString period, QString currPeriod, QString type, QString currency)
{
    QSqlQuery query(QSqlDatabase::database("transactions_connection"));
    query.prepare("SELECT category, value, currency, date FROM transactions WHERE type = ?");
    query.addBindValue(type);
    query.exec();
    QList<double> values;
    QStringList names;
    if(period == currPeriod)
    {
        while(query.next())
        {
            QString category = query.value(0).toString();
            if(!names.contains(category))
            {
                names.append(category);
                values.append(fabs(convertCurrency(query.value(1).toDouble(), query.value(2).toString(), currency)));
            }
            else
                values[names.indexOf(category)] += fabs(convertCurrency(query.value(1).toDouble(), query.value(2).toString(), currency));
        }
    }
    else
    {
        if(period == "Year")
        {
            while(query.next())
            {
                QDateTime dateTime = query.value(3).toDateTime();
                if(QString::number(dateTime.date().year()) == currPeriod)
                {
                    QString category = query.value(0).toString();
                    if(!names.contains(category))
                    {
                        names.append(category);
                        values.append(fabs(convertCurrency(query.value(1).toDouble(), query.value(2).toString(), currency)));
                    }
                    else
                        values[names.indexOf(category)] += fabs(convertCurrency(query.value(1).toDouble(), query.value(2).toString(), currency));
                }
            }
        }
        else if(period == "Month")
        {
            while(query.next())
            {
                QDateTime dateTime = query.value(3).toDateTime();
                if(QString::number(dateTime.date().month()) + "." + QString::number(dateTime.date().year()) == currPeriod)
                {
                    QString category = query.value(0).toString();
                    if(!names.contains(category))
                    {
                        names.append(category);
                        values.append(fabs(convertCurrency(query.value(1).toDouble(), query.value(2).toString(), currency)));
                    }
                    else
                        values[names.indexOf(category)] += fabs(convertCurrency(query.value(1).toDouble(), query.value(2).toString(), currency));
                }
            }
        }
    }
    QPieSeries *series = new QPieSeries;
    for(int i = 0; i < names.count(); i++)
    {
        series->append(names.value(i), values.value(i));
        series->slices().at(i)->setLabelVisible();
        series->slices().at(i)->setLabel(names.value(i) + ": " + QString::number(values.value(i), 'f', 2) + " " + currency);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(type + "s: " + currPeriod);
    chart->legend()->hide();
    return chart;
}

QStringList StatWinModel::getPeriods()
{
    QStringList list;
    list.append("All");
    list.append("Year");
    list.append("Month");
    return list;
}

QStringList StatWinModel::getList(QString period, QString type)
{
    QStringList list;
    if(period == "All")
    {
        list.append("All");
    }
    else
    {
        QSqlQuery query(QSqlDatabase::database("transactions_connection"));
        query.prepare("SELECT date FROM transactions WHERE type = ? ORDER BY dateTime(date) DESC");
        query.addBindValue(type);
        query.exec();
        if(period == "Year")
        {
            while(query.next())
            {
                QString year = QString::number(query.value(0).toDateTime().date().year());
                if(!list.contains(year))
                    list.append(year);
            }
        }
        else if(period == "Month")
        {
            while(query.next())
            {
                QString month = QString::number(query.value(0).toDateTime().date().month());
                QString year = QString::number(query.value(0).toDateTime().date().year());
                if(!list.contains(month + "." + year))
                    list.append(month + "." + year);
            }
        }
    }
    return list;
}
