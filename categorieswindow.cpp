#include "categorieswindow.h"
#include "ui_categorieswindow.h"
#include <QMessageBox>

CategoriesWindow::CategoriesWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoriesWindow)
{
    ui->setupUi(this);
    model = new CategoriesModel;
}

CategoriesWindow::~CategoriesWindow()
{
    delete ui;
}

void CategoriesWindow::closeEvent(QCloseEvent *event)
{
    emit settingsWindow();
    event->accept();
}

void CategoriesWindow::on_bAdd_clicked()
{
    if(model->addCategory(ui->eName->text()))
        QMessageBox::information(0, APP_NAME, "New category has been added!");
    ui->eName->clear();
}
