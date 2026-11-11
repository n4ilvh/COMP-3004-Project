#ifndef VIEWQUEUE_H
#define VIEWQUEUE_H

#include "featurepage.h"
#include "viewqueuecontrol.h"

class OrderQueue;
class QLabel;
class QPushButton;
class QTableWidget;

// Boundary class: the kitchen order queue (first in, first out).
class ViewQueue : public FeaturePage {
    Q_OBJECT
public:
    explicit ViewQueue(OrderQueue &queue, QWidget *parent = nullptr);

    int selectedOrderNumber() const;     // -1 if nothing is selected

public slots:
    void refresh() override;

signals:
    void viewDetailsRequested(int orderNumber);
    void completeOrderRequested(int orderNumber);

private slots:
    void updateButtons();

private:
    ViewQueueControl m_control;
    QLabel *m_summaryLabel;
    QTableWidget *m_table;
    QPushButton *m_detailsButton;
    QPushButton *m_completeButton;
};

#endif // VIEWQUEUE_H
