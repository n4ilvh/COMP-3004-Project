#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H

#include "order.h"
#include <QList>

// FIFO kitchen queue. Starts empty on every program run.
class OrderQueue {
public:
    void enqueue(const Order &order) { m_orders.append(order); }
    bool isEmpty() const { return m_orders.isEmpty(); }
    int size() const { return m_orders.size(); }
    const QList<Order> &orders() const { return m_orders; }
    Order *find(int orderNumber);
    bool remove(int orderNumber);

private:
    QList<Order> m_orders;
};

#endif // ORDERQUEUE_H
