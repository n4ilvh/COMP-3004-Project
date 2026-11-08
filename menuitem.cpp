#include "menuitem.h"

MenuItem::MenuItem(const QString &name, const QString &category, double price)
    : m_name(name), m_category(category), m_price(price)
{
}

void MenuItem::addIngredient(const QString &ingredient, double quantity, const QString &unit)
{
    m_ingredients.append({ingredient, quantity, unit});
}
