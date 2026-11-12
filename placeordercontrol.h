#ifndef PLACEORDERCONTROL_H
#define PLACEORDERCONTROL_H

#include "order.h"
#include <QList>
#include <QString>

class SystemData;
class Customer;
class MenuItem;


class PlaceOrderControl
{
public:
    explicit PlaceOrderControl(SystemData &data, Customer &customer);

    void addItem(const MenuItem &item);
    void clear();

    bool isEmpty() const {return m_cart.isEmpty();}
    const QList<OrderLine> &cart() const { return m_cart; }

    double subtotal() const;
    int maxPoints() const;
    double maxCredit(int points) const;

    Order preview(int points, double credit) const;
    bool canPlace(QString *reason) const;
    bool place(int points, double credit, QString *error);

private:
    SystemData &m_data;
    Customer *m_customer;
    QList<OrderLine> m_cart;
};

#endif // PLACEORDERCONTROL_H
