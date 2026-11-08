#include "order.h"
#include <cmath>

QString toString(OrderStatus status)
{
    switch (status) {
    case OrderStatus::InProgress: return "In Progress";
    case OrderStatus::Completed:  return "Completed";
    case OrderStatus::PickedUp:   return "Picked Up";
    case OrderStatus::Cancelled:  return "Cancelled";
    }
    return "Unknown";
}

QString toString(OrderType type)
{
    return type == OrderType::Online ? "Online" : "In Person";
}

double Order::roundCents(double value)
{
    return std::round(value * 100.0) / 100.0;
}

Order::Order(int orderNumber, const QString &customerUsername, const QString &customerName,
             OrderType type, const QDateTime &placedAt)
    : m_orderNumber(orderNumber),
      m_customerUsername(customerUsername),
      m_customerName(customerName),
      m_type(type),
      m_placedAt(placedAt)
{
}

void Order::addLine(const QString &itemName, int quantity, double unitPrice)
{
    m_lines.append({itemName, quantity, unitPrice});
}

void Order::applyPayment(int loyaltyPointsUsed, double accountCreditUsed)
{
    m_subtotal = 0.0;
    for (const OrderLine &line : m_lines)
        m_subtotal += line.lineTotal();
    m_subtotal = roundCents(m_subtotal);

    m_tax = roundCents(m_subtotal * TAX_RATE);
    m_finalPrice = roundCents(m_subtotal + m_tax);
    m_pointsUsed = loyaltyPointsUsed;
    m_creditUsed = accountCreditUsed;

    m_amountCharged = roundCents(m_finalPrice - m_pointsUsed - m_creditUsed);
    if (m_amountCharged < 0.0)
        m_amountCharged = 0.0;

    m_pointsEarned = (m_pointsUsed == 0) ? static_cast<int>(m_amountCharged / 3.0 + 1e-9) : 0;
}
