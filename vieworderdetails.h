#ifndef VIEWORDERDETAILS_H
#define VIEWORDERDETAILS_H

#include "order.h"
#include <QDialog>

class vieworderdetails : public QDialog
{
public:
    explicit vieworderdetails(const Order &order, QWidget *parent = nullptr);
};

#endif // VIEWORDERDETAILS_H
