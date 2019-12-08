#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QMessageBox>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::CustomizeWindowHint);
    setFixedSize(902, 542);
    ui->setupUi(this);
    newWalletWindow = new(NewWalletWindow);
    walletWindow = new(WalletWindow);
    connect(newWalletWindow, &NewWalletWindow::firstWindow, this, &MainWindow::show);
    connect(newWalletWindow, &NewWalletWindow::firstWindow, this, &MainWindow::prepareDatabase);
    connect(walletWindow, &WalletWindow::firstWindow, this, &MainWindow::show);
    connect(walletWindow, &WalletWindow::firstWindow, this, &MainWindow::prepareDatabase);
    prepareDatabase();
}

QString prepareTotalValue(QString str)
{
    QString result = "";
    int counter = 0;
    for(int i = str.count() - 1; i > -1; i--)
    {
        if(++counter % 4 == 0)
        {
            result = str[i] + "," + result;
            counter = 1;
        }
        else
            result = str[i] + result;
    }
    return result;
}

double convertToDollar(double value, QString currency)
{
    if(currency == "USD")
        return value;
    if(currency == "RUB")
        return (round(value * RUB_USD * 100)) / 100;
    if(currency == "BYN")
        return round(value * BYN_USD * 100) / 100;
    if(currency == "EUR")
        return round(value * EUR_USD * 100) / 100;
    if(currency == "LKR")
        return round(value * LKR_USD * 100) / 100;
}

void MainWindow::prepareDatabase()
{
    double sum = 0;
    QStringListModel *sListModel = new QStringListModel;
    QStringList sList;
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT id, date, currency, value FROM wallets");
    while(query.next())
    {
        sum += convertToDollar(query.value(3).toDouble(), query.value(2).toString());
        sList.append(query.value(0).toString());
    }
    if((sum > TOTAL_MAX) || (sum < TOTAL_MIN))
    {
        QMessageBox::warning(0, APP_NAME, "Total sum is out of range!\nApp can work incorrectly!"
                             "\nTo continue repair .sqlite file");
        ui->bAdd->setEnabled(false);
        ui->bSettings->setEnabled(false);
        ui->bStats->setEnabled(false);
        ui->list->setEnabled(false);
        ui->laTotal->setEnabled(false);
        ui->laTotal->setText("0 $");
    }
    else
    {
        std::ostringstream strs;
        strs << sum;
        std::string sumStr = strs.str();
        ui->laTotal->setText(QString::fromStdString(sumStr.append(" $")));
        sListModel->setStringList(sList);
        ui->list->setModel(sListModel);
    }
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
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT COUNT(*) FROM wallets");
    int rows = 0;
    if(query.next())
        rows = query.value(0).toInt();
    if(rows < 12)
    {
        newWalletWindow->show();
        this->close();
    }
    else
        QMessageBox::warning(0, APP_NAME, "Maximal amount of wallets is 12!");
}

void MainWindow::on_list_clicked(const QModelIndex &index)
{
    QString name = ui->list->model()->data(index).toString();
    walletWindow->name = name;
    walletWindow->show();
    this->close();
}

void MainWindow::on_bSettings_clicked()
{
    QMessageBox::information(0, APP_NAME, "Settings button was clicked!");
}

void MainWindow::on_bStats_clicked()
{
    QMessageBox::information(0, APP_NAME, "Statistics button was clicked!");
}
