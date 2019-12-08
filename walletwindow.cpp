#include "walletwindow.h"
#include "ui_walletwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QCloseEvent>
#include <QShowEvent>
#include <QSqlQueryModel>

WalletWindow::WalletWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WalletWindow)
{
    ui->setupUi(this);
    incomeWindow = new IncomeWindow;
    connect(incomeWindow, &IncomeWindow::walletWindow, this, &WalletWindow::show);
    connect(incomeWindow, &IncomeWindow::walletWindow, this, &WalletWindow::prepareDatabase);
}

void WalletWindow::prepareDatabase()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery query(QSqlDatabase::database("transactions_connection"));
    query.prepare("SELECT category, type, value, currency, date FROM transactions WHERE id = ?");
    query.addBindValue(name);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Value"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Currency"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
    ui->transactions->setModel(model);
    ui->transactions->resizeColumnsToContents();
}

void WalletWindow::showEvent(QShowEvent *event)
{
    event->accept();
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT id, date, currency, value FROM wallets WHERE id = ?");
    query.addBindValue(name);
    query.exec();
    while(query.next())
    {
        date = query.value(1).toString();
        currency = query.value(2).toString();
        value = query.value(3).toString();
        ui->laDate->setText(date);
        ui->laName->setText(name);
        ui->laValue->setText(value + " " + currency);
        prepareDatabase();
    }
}

WalletWindow::~WalletWindow()
{
    delete ui;
}

void WalletWindow::closeEvent(QCloseEvent *event)
{
    ui->laDate->clear();
    ui->laName->clear();
    ui->laValue->clear();
    emit firstWindow();
    event->accept();
}

void WalletWindow::on_bDelete_clicked()
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.prepare("DELETE FROM wallets WHERE id = ?");
    query.addBindValue(name);
    query.exec();

    QSqlQuery queryTransactions(QSqlDatabase::database("transactions_connection"));
    queryTransactions.prepare("DELETE FROM transactions WHERE id = ?");
    queryTransactions.addBindValue(name);
    queryTransactions.exec();
    this->close();
}

void WalletWindow::on_bSettings_clicked()
{
    QMessageBox::information(0, APP_NAME, "Settings button was pressed!");
}

void WalletWindow::on_bConsumption_clicked()
{
    QMessageBox::information(0, APP_NAME, "Consumption button was pressed!");
}

void WalletWindow::on_bIncome_clicked()
{
    incomeWindow->show();
    incomeWindow->currency = currency;
    incomeWindow->id = name;
    incomeWindow->value = value;
    this->hide();
}
