#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
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
    connect(newWalletWindow, &NewWalletWindow::firstWindow, this, &MainWindow::prepareWindow);
    connect(walletWindow, &WalletWindow::firstWindow, this, &MainWindow::show);
    connect(walletWindow, &WalletWindow::firstWindow, this, &MainWindow::prepareWindow);

    model->setCurrency("BYN");
    prepareWindow();
}

void MainWindow::prepareWindow()
{
    double sum = model->getSum();
    QStringList sList = model->getWalletsList();
    QStringListModel *sListModel = new QStringListModel;
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
        QString strSum = QString::number(sum, 'f', 2) + " " + model->getCurrency();
        ui->laTotal->setText(strSum);
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
