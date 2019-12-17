#include "incomewindow.h"
#include "ui_incomewindow.h"

IncomeWindow::IncomeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IncomeWindow)
{
    ui->setupUi(this);
    model = new IncomeWinModel;

    ui->categories->addItems(model->getCategories());
}

void IncomeWindow::showEvent(QShowEvent *event)
{
    event->accept();
    ui->value->setSuffix(" " + currency);
}

IncomeWindow::~IncomeWindow()
{
    delete ui;
}

void IncomeWindow::closeEvent(QCloseEvent *event)
{
    emit walletWindow();
    event->accept();
    ui->value->setValue(0);
}

void IncomeWindow::on_bAdd_clicked()
{
    model->setParameters(currency, id, value);
    if(model->addTransaction(ui->categories->currentText(), ui->value->value()))
        this->close();
}
