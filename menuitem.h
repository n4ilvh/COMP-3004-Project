#ifndef MENUITEM_H
#define MENUITEM_H

#include <QList>
#include <QString>

struct IngredientRequirement {
    QString ingredient;
    double quantity;
    QString unit;
};

class MenuItem {
public:
    MenuItem(const QString &name, const QString &category, double price);

    void addIngredient(const QString &ingredient, double quantity, const QString &unit);

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
