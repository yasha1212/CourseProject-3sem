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
    ui->categories->addItem("Clothes");
    ui->categories->addItem("Food");
    ui->categories->addItem("Transport");
    ui->categories->addItem("Salary");
    ui->categories->addItem("Sport");
    ui->categories->addItem("Other");
    ui->categories->addItem("Work");
    ui->categories->addItem("Car");
    ui->categories->addItem("Banks");
    ui->categories->addItem("Travelling");
    ui->categories->addItem("Rent");
    ui->categories->addItem("Taxes");
    ui->categories->addItem("Entertainment");
}

void IncomeWindow::showEvent(QShowEvent *event)
{
    ui->value->setSuffix(" " + currency);
    event->accept();
}

IncomeWindow::~IncomeWindow()
{
    delete ui;
}

void IncomeWindow::addIncome()
{
    QSqlQuery query(QSqlDatabase::database("transactions_connection"));
    query.prepare("INSERT INTO transactions(id, type, value, currency, date, category)"
                  "VALUES (:id, :type, :value, :currency, :date, :category)");
    query.bindValue(":id", id);
    double incomeValue = ui->value->value();
    QString type = incomeValue < 0? "Consumption": "Income";
    query.bindValue(":type", type);
    QString sign = incomeValue < 0? "": "+";
    query.bindValue(":value", sign + QString::number(incomeValue, 'f', 2));
    query.bindValue(":currency", currency);
    query.bindValue(":category", ui->categories->currentText());
    QString dateTime = QLocale{QLocale::English}.toString(QDateTime::currentDateTime(), DATE_FORMAT);
    query.bindValue(":date", dateTime);
    query.exec();

    QSqlQuery queryUpdate(QSqlDatabase::database("wallets_connection"));
    queryUpdate.prepare("UPDATE wallets SET value = :value WHERE id = :id");
    queryUpdate.bindValue(":id", id);
    double oldValue = value.toDouble();
    double resultValue = oldValue + incomeValue;
    sign = resultValue < 0? "": "+";
    queryUpdate.bindValue(":value", sign + QString::number(resultValue, 'f', 2));
    queryUpdate.exec();
}

void IncomeWindow::closeEvent(QCloseEvent *event)
{
    emit walletWindow();
    event->accept();
    ui->value->clear();
}

void IncomeWindow::on_bAdd_clicked()
{
    if(ui->categories->currentText().count() != 0)
    {
        if(ui->value->value() != 0)
        {
            addIncome();
            this->close();
        }
        else
            QMessageBox::warning(0, APP_NAME, "Value field must be filled!");
    }
    else
        QMessageBox::warning(0, APP_NAME, "Category must be selected!");
}
