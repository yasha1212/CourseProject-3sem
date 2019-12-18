#include "walletsettingswindow.h"
#include "ui_walletsettingswindow.h"
#include <QMessageBox>

WalletSettingsWindow::WalletSettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WalletSettingsWindow)
{
    ui->setupUi(this);
    model = new WalletSettingsWinModel;
}

WalletSettingsWindow::~WalletSettingsWindow()
{
    delete ui;
}

void WalletSettingsWindow::showEvent(QShowEvent *event)
{
    ui->eName->setText(name);
    model->name = name;
    ui->cbCurrency->clear();
    ui->cbCurrency->addItems(model->getCurrenciesList());
    if(inclusion == "yes")
        ui->rbInclude->setChecked(true);
    else
        ui->rbNotInclude->setChecked(true);
    event->accept();
}

void WalletSettingsWindow::closeEvent(QCloseEvent *event)
{
    emit walletWindow(name);
    event->accept();
}

void WalletSettingsWindow::on_rbInclude_clicked()
{
    model->setInclusion("yes");
    QMessageBox::information(0, APP_NAME, "Wallet value will be included in total value!");
}

void WalletSettingsWindow::on_rbNotInclude_clicked()
{
    model->setInclusion("no");
    QMessageBox::information(0, APP_NAME, "Wallet value will not be included in total value!");
}

void WalletSettingsWindow::on_bChange_clicked()
{
    QString initialName = name;
    if(model->setName(ui->eName->text()))
    {
        name = ui->eName->text();
        QMessageBox::information(0, APP_NAME, "Name was successfully changed! (" + initialName + "-->" + name + ")");
    }
}

void WalletSettingsWindow::on_bChangeCurrency_clicked()
{
    model->setCurrency(ui->cbCurrency->currentText());
    QMessageBox::information(0, APP_NAME, "Currency was successfully changed on " + ui->cbCurrency->currentText());
}
