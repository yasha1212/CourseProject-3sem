#ifndef CATEGORIESWINDOW_H
#define CATEGORIESWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include "categoriesmodel.h"

#define APP_NAME "MyWallet"

namespace Ui {
class CategoriesWindow;
}

class CategoriesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit CategoriesWindow(QWidget *parent = 0);
    ~CategoriesWindow();

signals:
    void settingsWindow();

private slots:
    void on_bAdd_clicked();

private:
    Ui::CategoriesWindow *ui;
    CategoriesModel *model;
    void closeEvent(QCloseEvent *event);
};

#endif // CATEGORIESWINDOW_H
