#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::CustomizeWindowHint);
    setFixedSize(902, 542);
    ui->setupUi(this);
    walletWindow = new(NewWalletWindow);
    connect(walletWindow, &NewWalletWindow::firstWindow, this, &MainWindow::show);
    connect(walletWindow, &NewWalletWindow::firstWindow, this, &MainWindow::ConnectDB);
    MainWindow::ConnectDB();
}

void MainWindow::ConnectDB()
{
    int Sum = 0;
    QStringListModel *sListModel = new QStringListModel;
    QStringList sList;
    QSqlQuery query;
    query.exec("CREATE table wallets"
               "(name text,"
               "date text,"
               "currency text,"
               "value text)");
    query.exec("SELECT name, date, currency, value FROM wallets");
    while(query.next())
    {
        Sum += query.value(3).toInt();
        sList.append(query.value(0).toString());
    }
    ui->laTotal->setText(QString::number(Sum) + "$");
    sListModel->setStringList(sList);
    ui->list->setModel(sListModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_bClose_clicked()
{
    this->close();
}

void MainWindow::on_bAdd_clicked()
{
    QSqlQuery query("SELECT COUNT(*) FROM wallets");
    int rows = 0;
    if(query.next())
        rows = query.value(0).toInt();
    if(rows < 12)
    {
        walletWindow->show();
        this->close();
    }
    else
        QMessageBox::warning(0, "Warning", "Maximal amount of wallets is 12!");
}

void MainWindow::on_list_clicked(const QModelIndex &index)
{
    QString name = ui->list->model()->data(index).toString();
    QMessageBox::information(0, "Information", name);
}
