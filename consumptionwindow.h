#ifndef CONSUMPTIONWINDOW_H
#define CONSUMPTIONWINDOW_H

#include <QWidget>
#include <QCloseEvent>

#define APP_NAME "MyWallet"
#define DATE_FORMAT "d MMMM yyyy, hh:mm:ss"

namespace Ui {
class ConsumptionWindow;
}

class ConsumptionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConsumptionWindow(QWidget *parent = 0);
    ~ConsumptionWindow();
    QString currency;
    QString id;
    QString value;

signals:
    void walletWindow();

private slots:
    void on_bAdd_clicked();

private:
    Ui::ConsumptionWindow *ui;
    void closeEvent(QCloseEvent *event);
    void addConsumption();
    void showEvent(QShowEvent *event);
};

#endif // CONSUMPTIONWINDOW_H
