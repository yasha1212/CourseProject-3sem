#include "statwindow.h"
#include "ui_statwindow.h"
#include <QChartView>
#include <QtCharts>

StatWindow::StatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatWindow)
{
    ui->setupUi(this);
    model = new StatWinModel;
}

StatWindow::~StatWindow()
{
    delete ui;
}

void StatWindow::closeEvent(QCloseEvent *event)
{
    emit firstWindow();
    event->accept();
}

void StatWindow::showEvent(QShowEvent *event)
{
    event->accept();
    ui->cbType->clear();
    ui->cbPeriod->clear();
    ui->cbType->addItems(model->getTypes());
    ui->cbPeriod->addItems(model->getPeriods());
}

void StatWindow::on_cbPeriod_currentTextChanged(const QString &arg1)
{
    ui->cbList->clear();
    ui->cbList->addItems(model->getList(arg1, ui->cbType->currentText() == "Incomes"? "Income": "Consumption"));
}

void StatWindow::on_cbType_currentTextChanged(const QString &arg1)
{
    ui->cbList->clear();
    ui->cbList->addItems(model->getList(ui->cbPeriod->currentText(), arg1 == "Incomes"? "Income": "Consumption"));
}

void StatWindow::on_bShow_clicked()
{
    QChartView *view = new QChartView(model->getChart(ui->cbPeriod->currentText(), ui->cbList->currentText(),
                                                      ui->cbType->currentText() == "Incomes"? "Income": "Consumption", currency));
    view->setRenderHint(QPainter::Antialiasing);
    view->setGeometry(300, 300, 500, 500);
    view->show();
}
