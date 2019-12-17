#include "walletsettingswindow.h"
#include "ui_walletsettingswindow.h"
#include <QMessageBox>

WalletSettingsWindow::WalletSettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WalletSettingsWindow)
{
    ui->setupUi(this);
    model = new WalletSettingsWinModel;
    ui->cbCurrency->addItems(model->getCurrenciesList());
}

WalletSettingsWindow::~WalletSettingsWindow()
{
    delete ui;
}

void WalletSettingsWindow::showEvent(QShowEvent *event)
{
    ui->eName->setText(name);
    model->name = name;
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
}

void WalletSettingsWindow::on_rbNotInclude_clicked()
{
    model->setInclusion("no");
}

void WalletSettingsWindow::on_bChange_clicked()
{
    model->setName(ui->eName->text());
    name = ui->eName->text();
}

void WalletSettingsWindow::on_bChangeCurrency_clicked()
{
    model->setCurrency(ui->cbCurrency->currentText());
}
