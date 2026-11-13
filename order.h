#ifndef ORDER_H
#define ORDER_H

#include <QDateTime>
#include <QList>
#include <QString>

enum class OrderStatus { InProgress, Completed, PickedUp, Cancelled };
enum class OrderType { Online, InPerson };

QString toString(OrderStatus status);
QString toString(OrderType type);

struct OrderLine {
    QString itemName;
    int quantity = 1;
    double unitPrice = 0.0;
    double lineTotal() const { return quantity * unitPrice; }
};

class Order {
public:
    static constexpr double TAX_RATE = 0.15;
    static double roundCents(double value);

    Order(int orderNumber, const QString &customerUsername, const QString &customerName,
          OrderType type, const QDateTime &placedAt);

    void addLine(const QString &itemName, int quantity, double unitPrice);

    // Computes subtotal, tax (15% of the FULL subtotal), final price, amount charged
    // and loyalty points earned (1 per $3 paid, rounded down, none if points were used).
    void applyPayment(int loyaltyPointsUsed, double accountCreditUsed);

    int orderNumber() const { return m_orderNumber; }
    const QString &customerUsername() const { return m_customerUsername; }
    const QString &customerName() const { return m_customerName; }
    OrderType type() const { return m_type; }
    const QDateTime &placedAt() const { return m_placedAt; }
    QString placedAtText() const { return m_placedAt.toString("yyyy-MM-dd:HH:mm"); }
    const QList<OrderLine> &lines() const { return m_lines; }

    double subtotal() const { return m_subtotal; }
    double tax() const { return m_tax; }
    double finalPrice() const { return m_finalPrice; }
    double amountCharged() const { return m_amountCharged; }
    int loyaltyPointsUsed() const { return m_pointsUsed; }
    double accountCreditUsed() const { return m_creditUsed; }
    int loyaltyPointsEarned() const { return m_pointsEarned; }
    void setLoyaltyPointsEarned(int p) { m_pointsEarned = p; }

    OrderStatus status() const { return m_status; }
    void setStatus(OrderStatus s) { m_status = s; }

private:
    int m_orderNumber;
    QString m_customerUsername;
    QString m_customerName;
    OrderType m_type;
    QDateTime m_placedAt;
    QList<OrderLine> m_lines;
    double m_subtotal = 0.0;
    double m_tax = 0.0;
    double m_finalPrice = 0.0;
    double m_amountCharged = 0.0;
    int m_pointsUsed = 0;
    double m_creditUsed = 0.0;
    int m_pointsEarned = 0;
    OrderStatus m_status = OrderStatus::InProgress;
};

#endif // ORDER_H
