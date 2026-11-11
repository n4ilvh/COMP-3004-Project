#ifndef DASHBOARDCONTROL_H
#define DASHBOARDCONTROL_H

#include <QList>
#include <QString>
#include <QStringList>

class Customer;
class Order;

struct AccountSummary {
    QString name;
    QString loyaltyNumber;
    QString email;
    QString homeAddress;
    int loyaltyPoints = 0;
    double accountCredit = 0.0;
};

struct OrderSummary {
    int orderNumber = 0;
    QString placedAt;
    QString type;
    QString status;
    QStringList items;
    double finalPrice = 0.0;
    double amountCharged = 0.0;
    int pointsUsed = 0;
    int pointsEarned = 0;
    bool pointsPending = false;    // earned points are added when the order is Completed
    double creditUsed = 0.0;
    double creditReceived = 0.0;   // refund for cancelled orders
    bool cancelled = false;
};

// Control class: gets the customer's account and orders for the dashboard.
class DashboardControl {
public:
    static constexpr int HISTORY_SIZE = 5;

    explicit DashboardControl(Customer &customer);

    AccountSummary account() const;

    bool hasCurrentOrder() const;
    OrderSummary currentOrder() const;
    QList<OrderSummary> orderHistory() const;     // newest first

    bool updateContactInfo(const QString &email, const QString &homeAddress,
                           QString &errorMessage);

private:
    static OrderSummary summarize(const Order &order);

    Customer &m_customer;
};

#endif // DASHBOARDCONTROL_H
