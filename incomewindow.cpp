#include "incomewindow.h"
#include "ui_incomewindow.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QMessageBox>
#include <QLocale>

IncomeWindow::IncomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IncomeWindow)
{
    ui->setupUi(this);
    ui->currency->setText(currency);
}

IncomeWindow::~IncomeWindow()
{
    delete ui;
}

void IncomeWindow::addIncome()
{
    QSqlQuery query(QSqlDatabase::database("transactions_connection"));
    QString integerVal = ui->eInteger->text();
    QString floatVal = ui->eFloat->text();
    QString newValue = "+" + integerVal + "." + floatVal;
    query.prepare("INSERT INTO transactions(id, type, value, currency, date, category)"
                  "VALUES (:id, :type, :value, :currency, :date, :category)");
    query.bindValue(":id", id);
    query.bindValue(":type", "income");
    query.bindValue(":value", newValue);
    query.bindValue(":currency", currency);
    query.bindValue(":category", "other");
    QString dateTime = QLocale{QLocale::English}.toString(QDateTime::currentDateTime(), DATE_FORMAT);
    query.bindValue(":date", dateTime);
    query.exec();

    QSqlQuery queryUpdate(QSqlDatabase::database("wallets_connection"));
    queryUpdate.prepare("UPDATE wallets SET value = :value WHERE id = :id");
    queryUpdate.bindValue(":id", id);
    double oldValue = value.toDouble();
    double incomeValue = newValue.toDouble();
    double resultValue = oldValue + incomeValue;
    QString sign = resultValue < 0? "-": "+";
    queryUpdate.bindValue(":value", sign + QString::number(resultValue));
    queryUpdate.exec();
}

void IncomeWindow::closeEvent(QCloseEvent *event)
{
    emit walletWindow();
    event->accept();
    ui->eFloat->clear();
    ui->eInteger->clear();
}

void IncomeWindow::on_bAdd_clicked()
{
    QString integerVal = ui->eInteger->text();
    QString floatVal = ui->eFloat->text();
    if(integerVal.count() != 0)
    {
        if(floatVal.count() == 0)
            ui->eFloat->setText("00");
        addIncome();
        this->close();
    }
    else
        QMessageBox::warning(0, APP_NAME, "Value field must be filled!");
}
