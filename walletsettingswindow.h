#ifndef WALLETSETTINGSWINDOW_H
#define WALLETSETTINGSWINDOW_H

#include <QWidget>
#include <QShowEvent>
#include <QCloseEvent>
#include "walletsettingswinmodel.h"

namespace Ui {
class WalletSettingsWindow;
}

class WalletSettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WalletSettingsWindow(QWidget *parent = 0);
    ~WalletSettingsWindow();
    QString name;
    QString currency;
    QString inclusion;

signals:
    void walletWindow(QString newName);

private slots:
    void on_rbInclude_clicked();

    void on_rbNotInclude_clicked();

    void on_bChange_clicked();

    void on_bChangeCurrency_clicked();

private:
    Ui::WalletSettingsWindow *ui;
    WalletSettingsWinModel *model;
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
};

#endif // WALLETSETTINGSWINDOW_H
