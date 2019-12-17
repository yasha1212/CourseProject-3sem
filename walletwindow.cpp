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
    walletSettingsWindow = new WalletSettingsWindow;
    model = new WalletWinModel;

    connect(incomeWindow, &IncomeWindow::walletWindow, this, &WalletWindow::show);
    connect(walletSettingsWindow, SIGNAL(walletWindow(QString)), this, SLOT(setName(QString)));
}

void WalletWindow::setName(QString newName)
{
    name = newName;
    this->show();
}

void WalletWindow::prepareTable()
{
    ui->transactions->setModel(model->getQueryModel());
    ui->transactions->resizeColumnsToContents();
}

void WalletWindow::showEvent(QShowEvent *event)
{
    event->accept();
    model->setName(name);
    date = model->getParameter("date");
    currency = model->getParameter("currency");
    value = model->getParameter("value");
    ui->laDate->setText(date);
    ui->laName->setText(name);
    ui->laValue->setText(value + " " + currency);
    prepareTable();
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
    model->deleteWallet();
    this->close();
}

void WalletWindow::on_bSettings_clicked()
{
    walletSettingsWindow->currency = currency;
    walletSettingsWindow->name = name;
    walletSettingsWindow->inclusion = model->getParameter("inclusion");
    walletSettingsWindow->show();
    this->hide();
}

void WalletWindow::on_bIncome_clicked()
{
    incomeWindow->currency = currency;
    incomeWindow->id = name;
    incomeWindow->value = value;
    incomeWindow->show();
    this->hide();
}
