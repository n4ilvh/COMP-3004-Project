#include "placeordercontrol.h"
#include "systemdata.h"
#include "customer.h"
#include "menuitem.h"
#include <QDateTime>
#include <algorithm>

PlaceOrderControl::PlaceOrderControl(SystemData &data, Customer &customer) : m_data(data), m_customer(&customer){


}

void PlaceOrderControl::clear(){
    m_cart.clear();
}

void PlaceOrderControl::addItem(const MenuItem &item){
    m_cart.append({item.name(), 1, item.price() });
}

double PlaceOrderControl::subtotal() const{
    double total = 0.0;
    for (const OrderLine &l : m_cart) total += l.lineTotal();
    return Order::roundCents(total);
}

int PlaceOrderControl::maxPoints() const{
    if (m_cart.isEmpty())
        return 0;
    const int half = static_cast<int>(subtotal()*0.5);
    return std::min(m_customer->loyaltyPoints(), half);
}

double PlaceOrderControl::maxCredit(int points) const{
    points = std::clamp(points, 0, maxPoints());
    const double finalPrice = preview(points, 0).finalPrice();
    return std::max(0.0, std::min(m_customer->accountCredit(), finalPrice - points));
}

Order PlaceOrderControl::preview(int points, double credit) const{
    Order tmp(0, m_customer->username(), m_customer->name(), OrderType::Online, QDateTime::currentDateTime());

    for (const OrderLine &l : m_cart)
        tmp.addLine(l.itemName, l.quantity, l.unitPrice);

    tmp.applyPayment(points, credit);
    return tmp;
}

bool PlaceOrderControl::canPlace(QString *reason) const{
    if(m_cart.isEmpty()){
        if(reason) *reason = QStringLiteral("Your cart is empty");
        return false;
    }
    if (m_customer->hasCurrentOrder()){
        if (reason) *reason = QStringLiteral("Only one order can be placed at a time");
        return false;
    }
    if (reason) reason->clear();
    return true;
}

bool PlaceOrderControl::place(int points, double credit, QString *error){
    if (!canPlace(error)) return false;

    points = std::clamp(points, 0, maxPoints());
    credit = std::clamp(credit, 0.0, maxCredit(points));

    Order order(m_data.nextOrderNumber(), m_customer->username(), m_customer->name(), OrderType::Online, QDateTime::currentDateTime());
    for (const OrderLine &l : m_cart)
        order.addLine(l.itemName, l.quantity, l.unitPrice);

    order.applyPayment(points, credit);
    order.setStatus(OrderStatus::InProgress);

    m_customer->setCurrentOrder(order);
    m_data.orderQueue().enqueue(order);
    m_customer->addLoyaltyPoints(-points);
    m_customer->addAccountCredit(-credit);

    m_cart.clear();
    return true;
}













