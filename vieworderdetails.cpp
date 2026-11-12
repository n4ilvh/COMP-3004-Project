#include "vieworderdetails.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>

static QString money(double v)
{
    return QString("%1").arg(v, 0, 'f', 2);
}

vieworderdetails::vieworderdetails(const Order &order, QWidget *parent)
    : QDialog(parent)
{

    setWindowTitle(tr("Order #%1 Details").arg(order.orderNumber()));
    setMinimumSize(520, 520);

    auto *info = new QFormLayout;
    info->addRow(tr("Customer:"), new QLabel(QString("%1 (%2)")
                                             .arg(order.customerName(), order.customerUsername())));
    info->addRow(tr("Type:"), new QLabel(toString(order.type())));
    info->addRow(tr("Placed:"), new QLabel(order.placedAtText()));
    info->addRow(tr("Status"), new QLabel(toString(order.status())));

    auto *table = new QTableWidget(order.lines().size(), 4);
    table->setHorizontalHeaderLabels({tr("Item"), tr("Quantity"), tr("Unit Price"), tr("Line Total")});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::NoSelection);

    for(int r = 0; r < order.lines().size(); r++){
        const OrderLine &l = order.lines()[r];
        table->setItem(r, 0, new QTableWidgetItem(l.itemName));
        table->setItem(r, 1, new QTableWidgetItem(QString::number(l.quantity)));
        table->setItem(r, 2, new QTableWidgetItem(money(l.unitPrice)));
        table->setItem(r, 3, new QTableWidgetItem(money(l.lineTotal())));
    }

    auto *totals = new QFormLayout;
    totals->addRow(tr("Subtotal:"), new QLabel(money(order.subtotal())));
    totals->addRow(tr("Tax:"), new QLabel(money(order.tax())));
    totals->addRow(tr("Finnal price:"), new QLabel(money(order.finalPrice())));
    totals->addRow(tr("Loyalty Points Used:"), new QLabel(QString::number(order.loyaltyPointsUsed())));
    totals->addRow(tr("Account Credit Used:"), new QLabel(money(order.accountCreditUsed())));
    auto *charged = new QLabel(money(order.amountCharged()));
    charged->setStyleSheet("font-weight: bold; font-size: 14pt;");
    totals->addRow(tr("Amount Charged:"), charged);
    totals->addRow(tr("Loyalty Points Earned:"), new QLabel(QString::number(order.loyaltyPointsEarned())));

    auto *closeBtn = new QPushButton(tr("Close"));
    connect(closeBtn, &QPushButton::clicked, this, &QDialog::accept);

    auto *main = new QVBoxLayout(this);
    main->addLayout(info);
    main->addWidget(table);
    main->addLayout(totals);
    main->addWidget(closeBtn, 0, Qt::AlignRight);
}
