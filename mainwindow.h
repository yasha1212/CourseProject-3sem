#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "newwalletwindow.h"
#include "walletwindow.h"

#define TOTAL_MAX 9999999999
#define TOTAL_MIN -9999999999
#define APP_NAME "MyWallet"
#define EUR_USD 1.1059
#define LKR_USD 0.0055
#define BYN_USD 0.4723
#define RUB_USD 0.0157

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bClose_clicked();

    void on_bAdd_clicked();

    void on_list_clicked(const QModelIndex &index);

    void on_bSettings_clicked();

    void on_bStats_clicked();

private:
    Ui::MainWindow *ui;
    NewWalletWindow *newWalletWindow;
    WalletWindow *walletWindow;
    void prepareDatabase();
};

#endif // MAINWINDOW_H
