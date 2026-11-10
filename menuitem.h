#ifndef MENUITEM_H
#define MENUITEM_H

#include <QList>
#include <QString>
#include "ingredient.h"

struct IngredientRequirement {
    Ingredient ingredient;
    double quantity;
};

class MenuItem {
public:
    MenuItem(const QString &name, const QString &category, double price);

    void addIngredient(Ingredient ingredient, double quantity);

    const QString &name() const { return m_name; }
    const QString &category() const { return m_category; }
    double price() const { return m_price; }
    const QList<IngredientRequirement> &ingredients() const { return m_ingredients; }

private:
    QString m_name;
    QString m_category;
    double m_price;
    QList<IngredientRequirement> m_ingredients;
};

#endif // MENUITEM_H
