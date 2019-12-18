#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "newwalletwindow.h"
#include "walletwindow.h"
#include "settingswindow.h"
#include "mainwinmodel.h"

#define WINDOW_SIZE_WIDTH 902
#define WINDOW_SIZE_HEIGHT 542

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
    SettingsWindow *settingsWindow;
    MainWinModel *model;
    void prepareWindow();
};

#endif // MAINWINDOW_H
