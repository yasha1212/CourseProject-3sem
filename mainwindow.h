#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "newwalletwindow.h"

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

private:
    Ui::MainWindow *ui;
    NewWalletWindow *walletWindow;
    void ConnectDB();
};

#endif // MAINWINDOW_H
