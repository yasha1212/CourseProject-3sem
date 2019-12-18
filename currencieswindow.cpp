#include "currencieswindow.h"
#include "ui_currencieswindow.h"
#include <QMessageBox>

CurrenciesWindow::CurrenciesWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CurrenciesWindow)
{
    ui->setupUi(this);
    model = new CategoriesModel;
}

CurrenciesWindow::~CurrenciesWindow()
{
    delete ui;
}

void CurrenciesWindow::closeEvent(QCloseEvent *event)
{
    emit settingsWindow();
    event->accept();
}

void CurrenciesWindow::on_bAdd_clicked()
{
    if(model->addCurrency(ui->eName->text(), ui->eFrom->value(), ui->eTo->value()))
    {
        QMessageBox::information(0, APP_NAME, "New currency has been added!");
        ui->eFrom->setValue(0);
        ui->eTo->setValue(0);
    }
    ui->eName->clear();
}
