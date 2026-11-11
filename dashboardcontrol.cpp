#include "dashboardcontrol.h"
#include "customer.h"
#include "order.h"
#include <QRegularExpression>

DashboardControl::DashboardControl(Customer &customer) : m_customer(customer)
{
}

AccountSummary DashboardControl::account() const
{
    AccountSummary summary;
    summary.name = m_customer.name();
    summary.loyaltyNumber = m_customer.loyaltyNumber();
    summary.email = m_customer.email();
    summary.homeAddress = m_customer.homeAddress();
    summary.loyaltyPoints = m_customer.loyaltyPoints();
    summary.accountCredit = m_customer.accountCredit();
    return summary;
}

bool DashboardControl::hasCurrentOrder() const
{
    return m_customer.hasCurrentOrder();
}

OrderSummary DashboardControl::currentOrder() const
{
    const Order *order = m_customer.currentOrder();
    return order ? summarize(*order) : OrderSummary();
}

QList<OrderSummary> DashboardControl::orderHistory() const
{
    QList<OrderSummary> result;
    const QList<Order> &all = m_customer.orderHistory().orders();
    for (int i = all.size() - 1; i >= 0 && result.size() < HISTORY_SIZE; --i) {
        const Order &order = all.at(i);
        if (order.status() == OrderStatus::PickedUp || order.status() == OrderStatus::Cancelled)
            result.append(summarize(order));
    }
    return result;
}

bool DashboardControl::updateContactInfo(const QString &email, const QString &homeAddress,
                                         QString &errorMessage)
{
    const QString newEmail = email.trimmed();
    const QString newAddress = homeAddress.trimmed();

    static const QRegularExpression emailPattern("^[^@\\s]+@[^@\\s]+\\.[^@\\s]+$");
    if (!emailPattern.match(newEmail).hasMatch()) {
        errorMessage = "Please enter a valid email address (for example name@example.com).";
        return false;
    }
    if (newAddress.isEmpty()) {
        errorMessage = "Home address cannot be empty.";
        return false;
    }

    m_customer.setEmail(newEmail);
    m_customer.setHomeAddress(newAddress);
    return true;
}

OrderSummary DashboardControl::summarize(const Order &order)
{
    OrderSummary summary;
    summary.orderNumber = order.orderNumber();
    summary.placedAt = order.placedAtText();
    summary.type = toString(order.type());
    summary.status = toString(order.status());
    for (const OrderLine &line : order.lines())
        summary.items << QString("%1 x %2").arg(QString::number(line.quantity), line.itemName);

    summary.finalPrice = order.finalPrice();
    summary.amountCharged = order.amountCharged();
    summary.pointsUsed = order.loyaltyPointsUsed();
    summary.pointsEarned = order.loyaltyPointsEarned();
    summary.pointsPending = order.status() == OrderStatus::InProgress && summary.pointsEarned > 0;
    summary.creditUsed = order.accountCreditUsed();

    // a cancelled order's amount charged is refunded as account credit
    summary.cancelled = order.status() == OrderStatus::Cancelled;
    summary.creditReceived = summary.cancelled ? order.amountCharged() : 0.0;
    return summary;
}
