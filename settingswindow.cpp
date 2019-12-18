#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QMessageBox>

SettingsWindow::SettingsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    model = new SettingsWinModel;
    currenciesWindow = new CurrenciesWindow;
    categoriesWindow = new CategoriesWindow;

    connect(categoriesWindow, &CategoriesWindow::settingsWindow, this, &SettingsWindow::show);
    connect(currenciesWindow, &CurrenciesWindow::settingsWindow, this, &SettingsWindow::show);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::showEvent(QShowEvent *event)
{
    event->accept();
    ui->cbCurrency->clear();
    ui->cbCurrency->addItems(model->getCurrencies());
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    emit firstWindow();
    event->accept();
}

void SettingsWindow::on_bChangeCurrency_clicked()
{
    model->setMainCurrency(ui->cbCurrency->currentText());
    QMessageBox::information(0, APP_NAME, "Main currency was successfully changed on " + ui->cbCurrency->currentText());
}

void SettingsWindow::on_bAbout_clicked()
{
    QMessageBox::information(0, APP_NAME, "This program was designed and created by Aleksey Shukan - \n"
                             "student of BSUIR, group № 851005. \n"
                             "Belarus, Minsk 2019. \n\n"
                             "MyWallet©");
}

void SettingsWindow::on_bEditCurr_clicked()
{
    currenciesWindow->show();
    this->hide();
}

void SettingsWindow::on_bEditCat_clicked()
{
    categoriesWindow->show();
    this->hide();
}
