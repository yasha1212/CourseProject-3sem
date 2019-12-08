#include "newwalletwindow.h"
#include "ui_newwalletwindow.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QCloseEvent>
#include <QMessageBox>
#include <QDateTime>
#include <QLocale>

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

bool isCorrectName(QString name)
{
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT id FROM wallets");
    while(query.next())
        if(query.value(0) == name)
            return false;
    return true;
}

void NewWalletWindow::addWallet()
{
    QString currency = ui->cbCurrency->currentText();
    if(currency.count() != 0)
    {
        QSqlQuery query(QSqlDatabase::database("wallets_connection"));
        query.prepare("INSERT INTO wallets (id, date, currency, value)"
                      "VALUES (:id, :date, :currency, :value)");
        query.bindValue(":id", ui->eName->text());
        QString dateTime = QLocale{QLocale::English}.toString(QDateTime::currentDateTime(), DATE_FORMAT);
        query.bindValue(":date", dateTime);
        query.bindValue(":currency", currency);
        QString sign = ui->value->value() < 0? "": "+";
        query.bindValue(":value", sign + QString::number(ui->value->value()));
        query.exec();
    }
    else
        QMessageBox::warning(0, APP_NAME, "Currency must be selected!");
}

void NewWalletWindow::on_bCreate_clicked()
{
    QString name = ui->eName->text();
    if(name.count() != 0)
    {
        if(isCorrectName(name))
        {
            addWallet();
            this->close();
        }
        else
            QMessageBox::warning(0, APP_NAME, "Such identifier is already exists!");
    }
    else
        QMessageBox::warning(0, APP_NAME, "Name field must be filled!");
}

void NewWalletWindow::closeEvent(QCloseEvent *event)
{
    ui->eName->clear();
    ui->value->clear();
    emit firstWindow();
    event->accept();
}
