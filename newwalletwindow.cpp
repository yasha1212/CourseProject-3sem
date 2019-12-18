#include "newwalletwindow.h"
#include "ui_newwalletwindow.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QCloseEvent>
#include <QMessageBox>

NewWalletWindow::NewWalletWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewWalletWindow)
{
    ui->setupUi(this);
    model = new NewWalletWinModel;

    ui->cbInclusion->addItem("Include in total");
    ui->cbInclusion->addItem("Don't include in total");
}

NewWalletWindow::~NewWalletWindow()
{
    delete ui;
}

void NewWalletWindow::showEvent(QShowEvent *event)
{
    event->accept();
    ui->cbCurrency->clear();
    ui->cbCurrency->addItems(model->getCurrenciesList());
}

void NewWalletWindow::on_bCreate_clicked()
{
    QString name = ui->eName->text();
    QString currency = ui->cbCurrency->currentText();
    QString inclusion = ui->cbInclusion->currentText();
    double value = ui->value->value();
    if(model->addWallet(name, currency, inclusion, value))
        this->close();
}

void NewWalletWindow::closeEvent(QCloseEvent *event)
{
    ui->eName->clear();
    ui->value->setValue(0);
    emit firstWindow();
    event->accept();
}
