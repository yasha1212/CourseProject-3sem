#ifndef WALLETSETTINGSWINMODEL_H
#define WALLETSETTINGSWINMODEL_H

#include <QString>

#define APP_NAME "MyWallet"

class WalletSettingsWinModel
{
public:
    WalletSettingsWinModel();
    void setInclusion(QString inclusion);
    void setName(QString newName);
    void setCurrency(QString currency);
    QString name;
    QStringList getCurrenciesList();
private:
    double convertCurrency(double value, QString walletCurrency, QString newCurrency);
    bool isCorrectName(QString name);
};

#endif // WALLETSETTINGSWINMODEL_H
