#include "viewqueuecontrol.h"
#include "orderqueue.h"

ViewQueueControl::ViewQueueControl(const OrderQueue &queue) : m_queue(queue)
{
}

QList<QueueEntry> ViewQueueControl::entries() const
{
    QList<QueueEntry> result;
    int position = 1;
    for (const Order &order : m_queue.orders()) {
        QueueEntry entry;
        entry.position = position++;
        entry.orderNumber = order.orderNumber();
        entry.customerName = order.customerName();
        entry.placedAt = order.placedAtText();
        entry.type = toString(order.type());
        entry.status = toString(order.status());
        for (const OrderLine &line : order.lines())
            entry.itemCount += line.quantity;
        result.append(entry);
    }
    return result;
}
