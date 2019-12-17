#ifndef INCOMEWINMODEL_H
#define INCOMEWINMODEL_H

#include <QStringList>
#include <QString>

#define APP_NAME "MyWallet"
#define DATE_FORMAT "yyyy-MM-dd hh:mm:ss"

class IncomeWinModel
{
public:
    IncomeWinModel();
    QStringList getCategories();
    void setParameters(QString currency, QString id, QString value);
    bool addTransaction(QString category, double incomeValue);
private:
    QString currency;
    QString id;
    QString value;
};

#endif // INCOMEWINMODEL_H
