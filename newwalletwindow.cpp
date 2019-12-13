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
    QSqlQuery query(QSqlDatabase::database("currencies_connection"));
    query.exec("SELECT id FROM currencies");
    while(query.next())
    {
        ui->cbCurrency->addItem(query.value(0).toString());
    }
    ui->cbInclusion->addItem("Include in total");
    ui->cbInclusion->addItem("Don't include in total");
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
    QString inclusion = ui->cbInclusion->currentText();
    if(currency.count() != 0)
    {
        if(inclusion.count() != 0)
        {
            inclusion = inclusion == "Include in total"? "yes": "no";
            QSqlQuery query(QSqlDatabase::database("wallets_connection"));
            query.prepare("INSERT INTO wallets (id, date, inclusion, currency, value)"
                          "VALUES (:id, :date, :inclusion, :currency, :value)");
            query.bindValue(":id", ui->eName->text());
            QString dateTime = QLocale{QLocale::English}.toString(QDateTime::currentDateTime(), DATE_FORMAT);
            query.bindValue(":date", dateTime);
            query.bindValue(":inclusion", inclusion);
            query.bindValue(":currency", currency);
            QString sign = ui->value->value() < 0? "": "+";
            query.bindValue(":value", sign + QString::number(ui->value->value(), 'f', 2));
            query.exec();
        }
        else
            QMessageBox::warning(0, APP_NAME, "Inclusion option must be selected!");
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
