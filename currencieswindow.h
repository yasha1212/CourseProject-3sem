#ifndef CURRENCIESWINDOW_H
#define CURRENCIESWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include "categoriesmodel.h"

#define APP_NAME "MyWallet"

namespace Ui {
class CurrenciesWindow;
}

class CurrenciesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CurrenciesWindow(QWidget *parent = 0);
    ~CurrenciesWindow();

signals:
    void settingsWindow();

private slots:
    void on_bAdd_clicked();

private:
    Ui::CurrenciesWindow *ui;
    CategoriesModel *model;
    void closeEvent(QCloseEvent *event);
};

#endif // CURRENCIESWINDOW_H
