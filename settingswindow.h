#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QShowEvent>
#include <QCloseEvent>
#include "settingswinmodel.h"
#include "currencieswindow.h"
#include "categorieswindow.h"

#define APP_NAME "MyWallet"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

signals:
    void firstWindow();

private slots:
    void on_bChangeCurrency_clicked();

    void on_bAbout_clicked();

    void on_bEditCurr_clicked();

    void on_bEditCat_clicked();

private:
    Ui::SettingsWindow *ui;
    SettingsWinModel *model;
    CategoriesWindow *categoriesWindow;
    CurrenciesWindow *currenciesWindow;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // SETTINGSWINDOW_H
