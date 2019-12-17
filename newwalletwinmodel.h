#ifndef NEWWALLETWINMODEL_H
#define NEWWALLETWINMODEL_H

#include <QStringList>

#define APP_NAME "MyWallet"
#define DATE_FORMAT "yyyy-MM-dd hh:mm:ss"

class NewWalletWinModel
{
public:
    NewWalletWinModel();
    QStringList getCurrenciesList();
    bool isCorrectName(QString name);
    bool addWallet(QString name, QString currency, QString inclusion, double value);
};

#endif // NEWWALLETWINMODEL_H
