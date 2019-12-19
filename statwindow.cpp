#include "statwindow.h"
#include "ui_statwindow.h"

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

}
