#ifndef STATWINDOW_H
#define STATWINDOW_H

#include <QWidget>
#include <QCloseEvent>
#include <QShowEvent>
#include "statwinmodel.h"

namespace Ui {
class StatWindow;
}

class StatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatWindow(QWidget *parent = 0);
    ~StatWindow();
    QString currency;

signals:
    void firstWindow();

private slots:
    void on_cbPeriod_currentTextChanged(const QString &arg1);

    void on_cbType_currentTextChanged(const QString &arg1);

    void on_bShow_clicked();

private:
    Ui::StatWindow *ui;
    StatWinModel *model;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // STATWINDOW_H
