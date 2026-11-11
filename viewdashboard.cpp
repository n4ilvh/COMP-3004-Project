#include "viewdashboard.h"
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QTableWidget>
#include <QVBoxLayout>

namespace {

enum HistoryColumn {
    ColNumber, ColDate, ColType, ColItems, ColFinalPrice, ColPoints, ColCredit, ColStatus,
    HistoryColumnCount
};

QString money(double amount)
{
    return QString("$%1").arg(amount, 0, 'f', 2);
}

QLabel *makeValueLabel(QWidget *parent)
{
    auto *label = new QLabel(parent);
    label->setWordWrap(true);
    label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    return label;
}

QTableWidgetItem *makeItem(const QString &text)
{
    auto *item = new QTableWidgetItem(text);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignTop);
    return item;
}

QString pointsText(const OrderSummary &order)
{
    if (order.pointsUsed > 0)
        return order.cancelled ? QString("Used %1 (returned)").arg(order.pointsUsed)
                               : QString("Used %1").arg(order.pointsUsed);
    if (order.pointsEarned > 0)
        return QString("Earned %1").arg(order.pointsEarned);
    return "None";
}

QString creditText(const OrderSummary &order)
{
    QStringList parts;
    if (order.creditReceived > 0.0)
        parts << "Received " + money(order.creditReceived) + " (refund)";
    if (order.creditUsed > 0.0)
        parts << "Used " + money(order.creditUsed) + (order.cancelled ? " (restored)" : "");
    return parts.isEmpty() ? QString("None") : parts.join("\n");
}

} // namespace

ViewDashboard::ViewDashboard(Customer &customer, QWidget *parent)
    : FeaturePage("My Dashboard", parent), m_control(customer)
{
    auto *topRow = new QHBoxLayout;
    topRow->addWidget(buildAccountBox(), 1);
    topRow->addWidget(buildCurrentOrderBox(), 1);

    contentLayout()->addLayout(topRow);
    contentLayout()->addWidget(buildHistoryBox(), 1);
}

QWidget *ViewDashboard::buildAccountBox()
{
    auto *box = new QGroupBox("Account", this);

    m_nameLabel = makeValueLabel(box);
    m_loyaltyNumberLabel = makeValueLabel(box);
    m_pointsLabel = makeValueLabel(box);
    m_creditLabel = makeValueLabel(box);
    m_emailLabel = makeValueLabel(box);
    m_addressLabel = makeValueLabel(box);

    auto *form = new QFormLayout;
    form->addRow("Name:", m_nameLabel);
    form->addRow("Loyalty points number:", m_loyaltyNumberLabel);
    form->addRow("Loyalty points balance:", m_pointsLabel);
    form->addRow("Account credit:", m_creditLabel);
    form->addRow("Email address:", m_emailLabel);
    form->addRow("Home address:", m_addressLabel);

    auto *editButton = new QPushButton("Update Contact Info...", box);
    editButton->setToolTip("Change your email address or home address");
    connect(editButton, &QPushButton::clicked, this, &ViewDashboard::editContactInfo);

    auto *layout = new QVBoxLayout(box);
    layout->addLayout(form);
    layout->addStretch();
    layout->addWidget(editButton, 0, Qt::AlignLeft);
    return box;
}

QWidget *ViewDashboard::buildCurrentOrderBox()
{
    auto *box = new QGroupBox("Current Order", this);

    auto *noOrderLabel = new QLabel("You have no current order.\n"
                                    "An order you place will appear here until it is picked up.",
                                    box);
    noOrderLabel->setWordWrap(true);
    noOrderLabel->setAlignment(Qt::AlignCenter);

    auto *details = new QWidget(box);
    m_orderNumberLabel = makeValueLabel(details);
    m_orderStatusLabel = makeValueLabel(details);
    m_orderStatusLabel->setStyleSheet("font-weight: bold;");
    m_orderPlacedLabel = makeValueLabel(details);
    m_orderItemsLabel = makeValueLabel(details);
    m_orderFinalPriceLabel = makeValueLabel(details);
    m_orderChargedLabel = makeValueLabel(details);
    m_orderPointsUsedLabel = makeValueLabel(details);
    m_orderPointsEarnedLabel = makeValueLabel(details);
    m_orderCreditUsedLabel = makeValueLabel(details);

    auto *form = new QFormLayout(details);
    form->setContentsMargins(0, 0, 0, 0);
    form->addRow("Order number:", m_orderNumberLabel);
    form->addRow("Order status:", m_orderStatusLabel);
    form->addRow("Placed:", m_orderPlacedLabel);
    form->addRow("Items purchased:", m_orderItemsLabel);
    form->addRow("Final price (incl. tax):", m_orderFinalPriceLabel);
    form->addRow("Amount charged:", m_orderChargedLabel);
    form->addRow("Loyalty points used:", m_orderPointsUsedLabel);
    form->addRow("Loyalty points earned:", m_orderPointsEarnedLabel);
    form->addRow("Account credit used:", m_orderCreditUsedLabel);

    m_currentOrderStack = new QStackedWidget(box);
    m_currentOrderStack->addWidget(noOrderLabel);
    m_currentOrderStack->addWidget(details);

    auto *layout = new QVBoxLayout(box);
    layout->addWidget(m_currentOrderStack);
    return box;
}

QWidget *ViewDashboard::buildHistoryBox()
{
    auto *box = new QGroupBox(
        QString("Order History (last %1 orders)").arg(DashboardControl::HISTORY_SIZE), this);

    m_historyTable = new QTableWidget(0, HistoryColumnCount, box);
    m_historyTable->setHorizontalHeaderLabels({"Order #", "Date", "Type", "Items Purchased",
                                               "Final Price (incl. tax)", "Loyalty Points",
                                               "Account Credit", "Status"});
    m_historyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_historyTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_historyTable->setSelectionMode(QAbstractItemView::SingleSelection);
    m_historyTable->setAlternatingRowColors(true);
    m_historyTable->setWordWrap(true);
    m_historyTable->verticalHeader()->setVisible(false);
    m_historyTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_historyTable->horizontalHeader()->setSectionResizeMode(ColItems, QHeaderView::Stretch);

    m_historyEmptyLabel = new QLabel("You have no past orders yet.", box);

    auto *note = new QLabel("Only orders that have been picked up or cancelled appear in the "
                            "order history.", box);
    note->setWordWrap(true);

    auto *layout = new QVBoxLayout(box);
    layout->addWidget(m_historyTable);
    layout->addWidget(m_historyEmptyLabel);
    layout->addWidget(note);
    return box;
}

void ViewDashboard::refresh()
{
    showAccount();
    showCurrentOrder();
    showHistory();
}

void ViewDashboard::showAccount()
{
    const AccountSummary account = m_control.account();
    m_nameLabel->setText(account.name);
    m_loyaltyNumberLabel->setText(account.loyaltyNumber);
    m_pointsLabel->setText(QString("%1 points").arg(account.loyaltyPoints));
    m_creditLabel->setText(money(account.accountCredit));
    m_emailLabel->setText(account.email);
    m_addressLabel->setText(account.homeAddress);
}

void ViewDashboard::showCurrentOrder()
{
    if (!m_control.hasCurrentOrder()) {
        m_currentOrderStack->setCurrentIndex(0);
        return;
    }

    const OrderSummary order = m_control.currentOrder();
    m_orderNumberLabel->setText(QString::number(order.orderNumber));
    m_orderStatusLabel->setText(order.status);
    m_orderPlacedLabel->setText(order.placedAt);
    m_orderItemsLabel->setText(order.items.join("\n"));
    m_orderFinalPriceLabel->setText(money(order.finalPrice));
    m_orderChargedLabel->setText(money(order.amountCharged));
    m_orderPointsUsedLabel->setText(QString::number(order.pointsUsed));

    QString earned = QString::number(order.pointsEarned);
    if (order.pointsPending)
        earned += " (added to your balance when the order is completed)";
    else if (order.pointsUsed > 0)
        earned += " (points are not earned when points are redeemed)";
    m_orderPointsEarnedLabel->setText(earned);

    m_orderCreditUsedLabel->setText(money(order.creditUsed));
    m_currentOrderStack->setCurrentIndex(1);
}

void ViewDashboard::showHistory()
{
    const QList<OrderSummary> history = m_control.orderHistory();

    m_historyTable->setRowCount(0);
    m_historyTable->setRowCount(history.size());
    for (int row = 0; row < history.size(); ++row) {
        const OrderSummary &order = history.at(row);
        m_historyTable->setItem(row, ColNumber, makeItem(QString::number(order.orderNumber)));
        m_historyTable->setItem(row, ColDate, makeItem(order.placedAt));
        m_historyTable->setItem(row, ColType, makeItem(order.type));
        m_historyTable->setItem(row, ColItems, makeItem(order.items.join("\n")));
        m_historyTable->setItem(row, ColFinalPrice, makeItem(money(order.finalPrice)));
        m_historyTable->setItem(row, ColPoints, makeItem(pointsText(order)));
        m_historyTable->setItem(row, ColCredit, makeItem(creditText(order)));
        m_historyTable->setItem(row, ColStatus, makeItem(order.status));
    }
    m_historyTable->resizeRowsToContents();
    m_historyEmptyLabel->setVisible(history.isEmpty());
}

void ViewDashboard::editContactInfo()
{
    const AccountSummary current = m_control.account();

    QDialog dialog(this);
    dialog.setWindowTitle("Update Contact Information");

    auto *emailEdit = new QLineEdit(current.email, &dialog);
    emailEdit->setMinimumWidth(320);
    auto *addressEdit = new QLineEdit(current.homeAddress, &dialog);

    auto *form = new QFormLayout;
    form->addRow("Email address:", emailEdit);
    form->addRow("Home address:", addressEdit);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, &dialog);

    auto *layout = new QVBoxLayout(&dialog);
    layout->addLayout(form);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, [&]() {
        QString error;
        if (m_control.updateContactInfo(emailEdit->text(), addressEdit->text(), error))
            dialog.accept();
        else
            QMessageBox::warning(&dialog, "Invalid Information", error);
    });

    if (dialog.exec() == QDialog::Accepted) {
        showAccount();
        QMessageBox::information(this, "Contact Information Updated",
                                 "Your email address and home address have been saved.");
    }
}
