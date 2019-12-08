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
    ui->cbSign->addItem("-");
    ui->cbSign->addItem("+");
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
    QString sign = ui->cbSign->currentText();

    if(currency.count() != 0)
    {
        if(sign.count() != 0)
        {
            QSqlQuery query(QSqlDatabase::database("wallets_connection"));
            QString integerVal = ui->eInteger->text();
            QString floatVal = ui->eFloat->text();
            query.prepare("INSERT INTO wallets (id, date, currency, value)"
                          "VALUES (:id, :date, :currency, :value)");
            query.bindValue(":id", ui->eName->text());
            QString dateTime = QLocale{QLocale::English}.toString(QDateTime::currentDateTime(), DATE_FORMAT);
            query.bindValue(":date", dateTime);
            query.bindValue(":currency", currency);
            query.bindValue(":value", sign + integerVal + "." + floatVal);
            query.exec();
        }
        else
            QMessageBox::warning(0, APP_NAME, "Sign must be selected!");
    }
    else
        QMessageBox::warning(0, APP_NAME, "Currency must be selected!");
}

void NewWalletWindow::on_bCreate_clicked()
{
    QString name = ui->eName->text();
    QString integerVal = ui->eInteger->text();
    QString floatVal = ui->eFloat->text();
    if(name.count() != 0)
    {
        if(isCorrectName(name))
        {
            if(integerVal.count() != 0)
            {
                if(floatVal.count() == 0)
                    ui->eFloat->setText("00");
                addWallet();
                this->close();
            }
            else
                QMessageBox::warning(0, APP_NAME, "Value field must be filled!");
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
    ui->eFloat->clear();
    ui->eInteger->clear();
    emit firstWindow();
    event->accept();
}
