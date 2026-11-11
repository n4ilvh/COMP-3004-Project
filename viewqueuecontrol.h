#ifndef VIEWQUEUECONTROL_H
#define VIEWQUEUECONTROL_H

#include <QList>
#include <QString>

class OrderQueue;

struct QueueEntry {
    int position = 0;          // 1 = next order to prepare
    int orderNumber = 0;
    QString customerName;
    QString placedAt;
    QString type;
    QString status;
    int itemCount = 0;
};

// Control class: reads the kitchen order queue for the queue screen.
class ViewQueueControl {
public:
    explicit ViewQueueControl(const OrderQueue &queue);

    QList<QueueEntry> entries() const;

private:
    const OrderQueue &m_queue;
};

#endif // VIEWQUEUECONTROL_H
