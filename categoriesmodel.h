#ifndef CATEGORIESMODEL_H
#define CATEGORIESMODEL_H

#include <QString>

#define APP_NAME "MyWallet"

class CategoriesModel
{
public:
    CategoriesModel();
    bool addCategory(QString id);
    bool addCurrency(QString id, double fromCoeff, double toCoeff);
};

#endif // CATEGORIESMODEL_H
