#ifndef NEWWALLETWINDOW_H
#define NEWWALLETWINDOW_H

#include <QWidget>

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
};

#endif // NEWWALLETWINDOW_H
