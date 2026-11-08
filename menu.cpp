#include "menu.h"

const QString Menu::SANDWICH = "Sandwich";
const QString Menu::HOT_BEVERAGE = "Hot Beverage";
const QString Menu::COLD_BEVERAGE = "Cold Beverage";

void Menu::addItem(const MenuItem &item)
{
    m_items.append(item);
}

QStringList Menu::categories() const
{
    return {SANDWICH, HOT_BEVERAGE, COLD_BEVERAGE};
}

QList<const MenuItem *> Menu::itemsInCategory(const QString &category) const
{
    QList<const MenuItem *> result;
    for (const MenuItem &item : m_items)
        if (item.category() == category)
            result.append(&item);
    return result;
}

const MenuItem *Menu::find(const QString &name) const
{
    for (const MenuItem &item : m_items)
        if (item.name() == name)
            return &item;
    return nullptr;
}
