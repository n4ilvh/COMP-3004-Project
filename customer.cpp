#include "customer.h"

Customer::Customer(const QString &name, const QString &username, const QString &loyaltyNumber,
                   const QString &email, const QString &homeAddress,
                   int loyaltyPoints, double accountCredit)
    : User(name, username),
      m_loyaltyNumber(loyaltyNumber),
      m_email(email),
      m_homeAddress(homeAddress),
      m_loyaltyPoints(loyaltyPoints),
      m_accountCredit(accountCredit)
{
}

void Customer::addAccountCredit(double delta)
{
    m_accountCredit = Order::roundCents(m_accountCredit + delta);
}

void Customer::setCurrentOrder(const Order &order)
{
    m_currentOrder = std::make_unique<Order>(order);
}

void Customer::recordHistoricalOrder(const Order &order)
{
    if (order.status() == OrderStatus::PickedUp) {
        // points/credit spent at payment, points earned when the order completed
        addLoyaltyPoints(-order.loyaltyPointsUsed() + order.loyaltyPointsEarned());
        addAccountCredit(-order.accountCreditUsed());
    } else if (order.status() == OrderStatus::Cancelled) {
        // points used are returned (net 0), credit used is restored (net 0),
        // and the amount charged is refunded as account credit.
        addAccountCredit(order.amountCharged());
    }
    m_history.add(order);
}
