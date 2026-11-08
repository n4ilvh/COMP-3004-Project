#ifndef ORDERHISTORY_H
#define ORDERHISTORY_H

#include "order.h"
#include <QList>

// Only orders that reached Picked Up or Cancelled belong here.
class OrderHistory {
public:
    void add(const Order &order) { m_orders.append(order); }
    const QList<Order> &orders() const { return m_orders; }
    QList<Order> lastOrders(int count) const;   // most recent first

private:
    QList<Order> m_orders;
};

#endif // ORDERHISTORY_H
