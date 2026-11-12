#ifndef PLACEORDER_H
#define PLACEORDER_H

#include "featurepage.h"
#include <QList>

class PlaceOrderControl;
class Customer;
class OrderLine;

namespace Ui {class PlaceOrder;}

class PlaceOrder : public FeaturePage{
    Q_OBJECT
public:
    explicit PlaceOrder(PlaceOrderControl &ordering, Customer &customer, QWidget *parent = nullptr);

public slots:
    void refresh() override;

private slots:
    void onConfirmClicked();

private:
    Ui::PlaceOrder *ui;
    QWidget *m_form;
    PlaceOrderControl &m_ordering;
    Customer &m_customer;
};

#endif // PLACEORDER_H
