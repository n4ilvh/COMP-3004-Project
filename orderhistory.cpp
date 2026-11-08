#include "orderhistory.h"

QList<Order> OrderHistory::lastOrders(int count) const
{
    QList<Order> result;
    for (int i = m_orders.size() - 1; i >= 0 && result.size() < count; --i)
        result.append(m_orders.at(i));
    return result;
}
