#ifndef WALLETWINMODEL_H
#define WALLETWINMODEL_H

#include <QSqlQueryModel>

#define APP_NAME "MyWallet"

class WalletWinModel
{
public:
    WalletWinModel();
    QSqlQueryModel* getQueryModel();
    void deleteWallet();
    QString getParameter(QString parameter);
    void setName(QString id);
private:
    QString name;
};

#endif // WALLETWINMODEL_H
