#include "consumptionwindow.h"
#include "ui_consumptionwindow.h"
#include <QSqlQuery>
#include <QDateTime>
#include <QMessageBox>
#include <QLocale>

ConsumptionWindow::ConsumptionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsumptionWindow)
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

void ConsumptionWindow::showEvent(QShowEvent *event)
{
    ui->value->setSuffix(" " + currency);
    event->accept();
}

ConsumptionWindow::~ConsumptionWindow()
{
    delete ui;
}

void ConsumptionWindow::closeEvent(QCloseEvent *event)
{
    emit walletWindow();
    event->accept();
    ui->value->clear();
}

void ConsumptionWindow::addConsumption()
{
    QSqlQuery query(QSqlDatabase::database("transactions_connection"));
    query.prepare("INSERT INTO transactions(id, type, value, currency, date, category)"
                  "VALUES (:id, :type, :value, :currency, :date, :category)");
    query.bindValue(":id", id);
    query.bindValue(":type", "consumption");
    QString sign = ui->value->value() < 0? "": "+";
    query.bindValue(":value", sign + QString::number(ui->value->value()));
    query.bindValue(":currency", currency);
    query.bindValue(":category", ui->categories->currentText());
    QString dateTime = QLocale{QLocale::English}.toString(QDateTime::currentDateTime(), DATE_FORMAT);
    query.bindValue(":date", dateTime);
    query.exec();

    QSqlQuery queryUpdate(QSqlDatabase::database("wallets_connection"));
    queryUpdate.prepare("UPDATE wallets SET value = :value WHERE id = :id");
    queryUpdate.bindValue(":id", id);
    double oldValue = value.toDouble();
    double incomeValue = ui->value->value();
    double resultValue = oldValue + incomeValue;
    sign = resultValue < 0? "": "+";
    queryUpdate.bindValue(":value", sign + QString::number(resultValue));
    queryUpdate.exec();
}

void ConsumptionWindow::on_bAdd_clicked()
{
    if(ui->categories->currentText().count() != 0)
    {
        if(ui->value->value() != 0)
        {
            addConsumption();
            this->close();
        }
        else
            QMessageBox::warning(0, APP_NAME, "Value field must be filled!");
    }
    else
        QMessageBox::warning(0, APP_NAME, "Category must be selected!");
}
