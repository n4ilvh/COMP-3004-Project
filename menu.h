#ifndef MENU_H
#define MENU_H

#include "menuitem.h"
#include <QList>
#include <QStringList>

class Menu {
public:
    static const QString SANDWICH;
    static const QString HOT_BEVERAGE;
    static const QString COLD_BEVERAGE;

    void addItem(const MenuItem &item);
    const QList<MenuItem> &items() const { return m_items; }
    QStringList categories() const;                       // in display order
    QList<const MenuItem *> itemsInCategory(const QString &category) const;
    const MenuItem *find(const QString &name) const;

private:
    QList<MenuItem> m_items;
};

#endif // MENU_H
