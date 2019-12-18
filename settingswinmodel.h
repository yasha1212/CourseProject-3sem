#ifndef SETTINGSWINMODEL_H
#define SETTINGSWINMODEL_H

#include <QStringList>

class SettingsWinModel
{
public:
    SettingsWinModel();
    QStringList getCurrencies();
    void setMainCurrency(QString currency);
};

#endif // SETTINGSWINMODEL_H
