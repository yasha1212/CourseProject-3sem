#ifndef NEWWALLETWINDOW_H
#define NEWWALLETWINDOW_H

#include <QWidget>
#include "newwalletwinmodel.h"

namespace Ui {
class NewWalletWindow;
}

class NewWalletWindow : public QWidget
{
    Q_OBJECT

public:
    explicit NewWalletWindow(QWidget *parent = 0);
    ~NewWalletWindow();

signals:
    void firstWindow();

private slots:
    void on_bCreate_clicked();

private:
    Ui::NewWalletWindow *ui;
    NewWalletWinModel *model;
    void closeEvent(QCloseEvent *event);
};

#endif // NEWWALLETWINDOW_H
