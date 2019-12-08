#ifndef NEWWALLETWINDOW_H
#define NEWWALLETWINDOW_H

#include <QWidget>

#define APP_NAME "MyWallet"
#define DATE_FORMAT "d MMMM yyyy, hh:mm:ss"

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
    void closeEvent(QCloseEvent *event);
    void addWallet();
};

#endif // NEWWALLETWINDOW_H
