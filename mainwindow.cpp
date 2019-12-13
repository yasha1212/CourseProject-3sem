#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <sstream>
#include <QStringListModel>
#include "QtSql/QSqlQuery"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowFlags(Qt::CustomizeWindowHint);
    setFixedSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
    ui->setupUi(this);

    newWalletWindow = new(NewWalletWindow);
    walletWindow = new(WalletWindow);
    model = new(MainWinModel);

    connect(newWalletWindow, &NewWalletWindow::firstWindow, this, &MainWindow::show);
    connect(newWalletWindow, &NewWalletWindow::firstWindow, this, &MainWindow::prepareDatabase);
    connect(walletWindow, &WalletWindow::firstWindow, this, &MainWindow::show);
    connect(walletWindow, &WalletWindow::firstWindow, this, &MainWindow::prepareDatabase);

    model->setCurrency("BYN");
    prepareDatabase();
}

void MainWindow::prepareDatabase()
{
    double sum = 0;
    QStringListModel *sListModel = new QStringListModel;
    QStringList sList;
    QSqlQuery query(QSqlDatabase::database("wallets_connection"));
    query.exec("SELECT id, date, inclusion, currency, value FROM wallets");
    while(query.next())
    {
        if(query.value(2) == "yes")
            sum += model->convertToMainCurrency(query.value(4).toDouble(), query.value(3).toString());
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
        ui->laTotal->setText("0 " + model->getCurrency());
    }
    else
    {
        std::ostringstream strs;
        strs << sum;
        std::string sumStr = strs.str();
        std::string appendStr = " " + model->getCurrency().toStdString();
        ui->laTotal->setText(QString::fromStdString(sumStr.append(appendStr)));
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
    if(model->isReadyForAdding())
    {
        newWalletWindow->show();
        this->close();
    }
}

void MainWindow::on_list_clicked(const QModelIndex &index)
{
    QString walletName = ui->list->model()->data(index).toString();
    walletWindow->name = walletName;
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
