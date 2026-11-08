#include "orderqueue.h"

Order *OrderQueue::find(int orderNumber)
{
    for (Order &o : m_orders)
        if (o.orderNumber() == orderNumber)
            return &o;
    return nullptr;
}

bool OrderQueue::remove(int orderNumber)
{
    for (int i = 0; i < m_orders.size(); ++i) {
        if (m_orders.at(i).orderNumber() == orderNumber) {
            m_orders.removeAt(i);
            return true;
        }
    }
    return false;
}
