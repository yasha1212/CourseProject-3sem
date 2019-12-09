#ifndef INCOMEWINDOW_H
#define INCOMEWINDOW_H

#include <QWidget>
#include <QCloseEvent>

#define APP_NAME "MyWallet"
#define DATE_FORMAT "yyyy-MM-dd hh:mm:ss"

namespace Ui {
class IncomeWindow;
}

class IncomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit IncomeWindow(QWidget *parent = 0);
    ~IncomeWindow();
    QString currency;
    QString id;
    QString value;

signals:
    void walletWindow();

private slots:
    void on_bAdd_clicked();

private:
    Ui::IncomeWindow *ui;
    void closeEvent(QCloseEvent *event);
    void addIncome();
    void showEvent(QShowEvent *event);
};

#endif // INCOMEWINDOW_H
