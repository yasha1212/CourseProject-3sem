#ifndef MAINWINMODEL_H
#define MAINWINMODEL_H

#include <QString>

#define TOTAL_MAX 9999999999
#define TOTAL_MIN -9999999999
#define APP_NAME "MyWallet"

class MainWinModel
{
public:
    MainWinModel();
    bool isReadyForAdding();
    void setCurrency();
    QString getCurrency();
    double convertToMainCurrency(double value, QString walletCurrency);
    double getSum();
    QStringList getWalletsList();
private:
    QString currency;
};

#endif // MAINWINMODEL_H
