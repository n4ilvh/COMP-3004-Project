#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"
#include "order.h"
#include "orderhistory.h"
#include <memory>

class Customer : public User {
public:
    Customer(const QString &name, const QString &username, const QString &loyaltyNumber,
             const QString &email, const QString &homeAddress,
             int loyaltyPoints, double accountCredit);

    QString userType() const override { return "Customer"; }

    const QString &loyaltyNumber() const { return m_loyaltyNumber; }
    const QString &email() const { return m_email; }
    const QString &homeAddress() const { return m_homeAddress; }
    void setEmail(const QString &e) { m_email = e; }
    void setHomeAddress(const QString &a) { m_homeAddress = a; }

    int loyaltyPoints() const { return m_loyaltyPoints; }
    double accountCredit() const { return m_accountCredit; }
    void addLoyaltyPoints(int delta) { m_loyaltyPoints += delta; }
    void addAccountCredit(double delta);

    const OrderHistory &orderHistory() const { return m_history; }

    // Current (In Progress / Completed) order - at most one at a time.
    bool hasCurrentOrder() const { return m_currentOrder != nullptr; }
    Order *currentOrder() { return m_currentOrder.get(); }
    void setCurrentOrder(const Order &order);

    // Used when loading default data: stores a Picked Up / Cancelled order in the
    // history AND applies its effect to the balances so they stay consistent.
    void recordHistoricalOrder(const Order &order);

private:
    QString m_loyaltyNumber;
    QString m_email;
    QString m_homeAddress;
    int m_loyaltyPoints;
    double m_accountCredit;
    OrderHistory m_history;
    std::unique_ptr<Order> m_currentOrder;
};

#endif // CUSTOMER_H
