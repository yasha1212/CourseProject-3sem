#include "walletwinmodel.h"
#include <QSqlQuery>

WalletWinModel::WalletWinModel()
{
}

QSqlQueryModel* WalletWinModel::getQueryModel()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery query(QSqlDatabase::database("transactions_connection"));
    query.prepare("SELECT category, type, value, currency, date FROM transactions WHERE id = ? ORDER BY dateTime(date) DESC");
    query.addBindValue(name);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Value"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Currency"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
    return model;
}

void WalletWinModel::setName(QString id)
{
    this->name = id;
}

void WalletWinModel::deleteWallet()
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.prepare("DELETE FROM wallets WHERE id = ?");
    query.addBindValue(name);
    query.exec();

    QSqlQuery queryTransactions(QSqlDatabase::database("transactions_connection"));
    queryTransactions.prepare("DELETE FROM transactions WHERE id = ?");
    queryTransactions.addBindValue(name);
    queryTransactions.exec();
}

QString WalletWinModel::getParameter(QString parameter)
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT id, " + parameter + " FROM wallets WHERE id = ?");
    query.addBindValue(name);
    query.exec();
    while(query.next())
        return query.value(1).toString();
}
