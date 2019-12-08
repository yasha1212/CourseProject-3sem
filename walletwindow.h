#ifndef WALLETWINDOW_H
#define WALLETWINDOW_H

#include <QWidget>
#include "incomewindow.h"

#define APP_NAME "MyWallet"

namespace Ui {
class WalletWindow;
}

class WalletWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WalletWindow(QWidget *parent = 0);
    ~WalletWindow();
    QString name;
    QString date;
    QString currency;
    QString value;

signals:
    void firstWindow();

private slots:
    void on_bDelete_clicked();

    void on_bSettings_clicked();

    void on_bConsumption_clicked();

    void on_bIncome_clicked();

private:
    Ui::WalletWindow *ui;
    IncomeWindow *incomeWindow;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    void prepareDatabase();
};

#endif // WALLETWINDOW_H
