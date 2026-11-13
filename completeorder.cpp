#include "completeorder.h"

#include <QSignalBlocker>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableWidget>
#include <QVBoxLayout>

static QString money(double v) { return QString("$%1").arg(v, 0, 'f', 2); }

completeorder::completeorder(const Order &order,int availablePoints, double availableCredit, QWidget *parent)
    : QDialog(parent), m_order(order), m_availablePoints(availablePoints), m_availableCredit(availableCredit)
{

    setWindowTitle(tr("Complete Order #%1").arg(order.orderNumber()));
    setMinimumSize(520, 520);
    setupUi();
    fillTable();
    m_order.applyPayment(0,0);
    updatePreview();
}

void completeorder::setupUi()
{
    auto *header = new QLabel(tr("Customer: %1 (%2)  |  %3  |  %4").arg(m_order.customerName(),
                                           m_order.customerUsername(),
                                           toString(m_order.type()),
                                           m_order.placedAtText()));

    m_table = new QTableWidget(0, 4);
    m_table->setHorizontalHeaderLabels({tr("Item"), tr("Qty"), tr("Unit Price"), tr("Line Total")});
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionMode(QAbstractItemView::NoSelection);

    //inputs for payments
    m_pointsSpin = new QSpinBox;
    m_pointsSpin->setRange(0, m_availablePoints);
    m_pointsSpin->setSuffix(tr(" pts"));

    m_creditSpin = new QDoubleSpinBox;
    m_creditSpin->setRange(0.0, m_availableCredit);
    m_creditSpin->setDecimals(2);
    m_creditSpin->setPrefix("$");

    auto *payForm = new QFormLayout;
    payForm->addRow(tr("Loyalty points to use (have %1):").arg(m_availablePoints), m_pointsSpin);
    payForm->addRow(tr("Account credit to use (have %1):").arg(money(m_availableCredit)), m_creditSpin);

    m_subtotalLbl = new QLabel;
    m_taxLbl = new QLabel;
    m_finalLbl = new QLabel;
    m_chargedLbl = new QLabel;
    m_earnedLbl = new QLabel;
    m_finalLbl->setStyleSheet("font-weight: bold;");
    m_chargedLbl->setStyleSheet("font-weight: bold; font-size 14pt;");

    auto *totals = new QFormLayout;
    totals->addRow(tr("Subtotal:"), m_subtotalLbl);
    totals->addRow(tr("Tax (%1):").arg(Order::TAX_RATE *100), m_taxLbl);
    totals->addRow(tr("Final Price:"), m_finalLbl);
    totals->addRow(tr("Amount Charged:"), m_chargedLbl);
    totals->addRow(tr("Loyalty points earned:"), m_earnedLbl);


    m_confirmBtn = new QPushButton(tr("Complete Order"));
    m_confirmBtn->setDefault(true);
    auto *cancelBtn = new QPushButton(tr("Cancel"));

    auto *btns = new QHBoxLayout;
    btns->addStretch();
    btns->addWidget(cancelBtn);
    btns->addWidget(m_confirmBtn);

    auto *main = new QVBoxLayout(this);
    main->addWidget(header);
    main->addWidget(m_table);
    main->addLayout(payForm);
    main->addLayout(totals);
    main->addLayout(btns);

    connect(m_pointsSpin, qOverload<int>(&QSpinBox::valueChanged),
            this, &completeorder::updatePreview);

    connect(m_creditSpin, qOverload<double>(&QDoubleSpinBox::valueChanged),
            this, &completeorder::updatePreview);

    connect(m_confirmBtn, &QPushButton::clicked, this, &completeorder::onConfirm);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);

}

void completeorder::fillTable()
{

    const auto &lines = m_order.lines();
    m_table->setRowCount(lines .size());

    for(int r = 0; r < lines.size(); r++){
        const OrderLine &l = lines[r];
        m_table->setItem(r, 0, new QTableWidgetItem(l.itemName));
        m_table->setItem(r, 1, new QTableWidgetItem(QString::number(l.quantity)));
        m_table->setItem(r, 2, new QTableWidgetItem(money(l.unitPrice)));
        m_table->setItem(r, 3, new QTableWidgetItem(money(l.lineTotal())));
    }

}

void completeorder::updatePreview()
{

    const double finalPrice = m_order.finalPrice();

    QSignalBlocker b1(m_pointsSpin);
    QSignalBlocker b2(m_creditSpin);

    int maxPoints = qMin(m_availablePoints, static_cast<int>(finalPrice - m_creditSpin->value() +1e-9));

    m_pointsSpin->setMaximum(qMax(0, maxPoints));

    double maxCredit = qMin(m_availableCredit, Order::roundCents(finalPrice - m_pointsSpin->value()));

    m_creditSpin->setMaximum(qMax(0.0, maxCredit));

    m_order.applyPayment(m_pointsSpin->value(), m_creditSpin->value());

    m_subtotalLbl->setText(money(m_order.subtotal()));
    m_taxLbl->setText(money(m_order.tax()));
    m_finalLbl->setText(money(m_order.finalPrice()));
    m_chargedLbl->setText(money(m_order.amountCharged()));
    m_earnedLbl->setText(m_order.loyaltyPointsUsed() > 0 ? tr("0 (none earned when points are used)")
                                                           : QString::number(m_order.loyaltyPointsEarned()));

}

void completeorder::onConfirm()
{

    if(m_order.lines().isEmpty()){
        QMessageBox::warning(this, tr("Empty order"), tr("This Order has no Items"));
        return;
    }
    m_order.applyPayment(m_pointsSpin->value(), m_creditSpin->value());
    m_order.setStatus(OrderStatus::Completed);
    emit orderCompleted(m_order);
    accept();
}
