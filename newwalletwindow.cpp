#include "newwalletwindow.h"
#include "ui_newwalletwindow.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"

NewWalletWindow::NewWalletWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewWalletWindow)
{
    ui->setupUi(this);
    ui->cbCurrency->addItem("RUB");
    ui->cbCurrency->addItem("EUR");
    ui->cbCurrency->addItem("USD");
    ui->cbCurrency->addItem("BYN");
    ui->cbCurrency->addItem("LKR");
}

NewWalletWindow::~NewWalletWindow()
{
    delete ui;
}

void NewWalletWindow::on_bCreate_clicked()
{
    QSqlQuery query;
    query.exec("CREATE table wallets"
               "(name text,"
               "date text,"
               "currency text,"
               "value text)");
    query.prepare("INSERT INTO wallets (name, date, currency, value)"
                  "VALUES (:name, :date, :currency, :value)");
    query.bindValue(":name", ui->eName->text());
    query.bindValue(":date", "111");
    query.bindValue(":currency", ui->cbCurrency->currentText());
    query.bindValue(":value", ui->eValue->text());
    query.exec();

    this->close();
    emit firstWindow();
}
