#include "menuitem.h"

MenuItem::MenuItem(const QString &name, const QString &category, double price)
    : m_name(name), m_category(category), m_price(price)
{
}

void MenuItem::addIngredient(Ingredient ingredient, double quantity)
{
    m_ingredients.append({ingredient, quantity});
}
