#include "placeorder.h"
#include "ui_PlaceOrder.h"
#include "placeordercontrol.h"
#include "customer.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidget>

PlaceOrder::PlaceOrder(PlaceOrderControl &ordering, Customer &customer, QWidget *parent) : FeaturePage("Place Order", parent), ui(new Ui::PlaceOrder), m_form(new QWidget), m_ordering(ordering), m_customer(customer)
{
    ui->setupUi(m_form);
    contentLayout()->addWidget(m_form);
    connect(ui->pushButton, &QPushButton::clicked, this, &PlaceOrder::onConfirmClicked);
}

void PlaceOrder::refresh(){
    const QList<OrderLine> &lines = m_ordering.cart();
    ui->cartTable->setRowCount(lines.size());
    for (int i = 0; i < lines.size(); i++) {
        ui->cartTable->setItem(i, 0, new QTableWidgetItem(lines[i].itemName));
        ui->cartTable->setItem(i, 1, new QTableWidgetItem(QString::number(lines[i].quantity)));
        ui->cartTable->setItem(i, 2, new QTableWidgetItem(QString("$%1").arg(lines[i].unitPrice, 0, 'f', 2)));
        ui->cartTable->setItem(i, 3, new QTableWidgetItem(QString("$%1").arg(lines[i].lineTotal(), 0, 'f', 2)));
    }

    ui->spinBox->setMaximum(m_ordering.maxPoints());
    ui->doubleSpinBox->setMaximum(m_ordering.maxCredit(ui->spinBox->value()));

    const Order p = m_ordering.preview(ui->spinBox->value(), ui->doubleSpinBox->value());
    ui->Subtotal->setText(QString("$%1").arg(p.subtotal(), 0, 'f', 2));
}

void PlaceOrder::onConfirmClicked(){
    QString error;
    const int points = ui->spinBox->value();
    const double credit = ui->doubleSpinBox->value();

    if (!m_ordering.place(points, credit, &error)) {
        QMessageBox::warning(this, "Cannot place order", error);
        return;
    }

    QMessageBox::information(this, "Order placed", "Thank you for your purchase.");
    emit backRequested();
    refresh();
}
