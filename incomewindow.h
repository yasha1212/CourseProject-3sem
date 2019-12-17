#ifndef INCOMEWINDOW_H
#define INCOMEWINDOW_H

#include "incomewinmodel.h"
#include <QWidget>
#include <QCloseEvent>

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
    IncomeWinModel *model;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // INCOMEWINDOW_H
