#ifndef COMPLETEORDER_H
#define COMPLETEORDER_H

#include "order.h"
#include <QDialog>

class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class  QTableWidget;
class QPushButton;

class completeorder : public QDialog
{
    Q_OBJECT
public:
    completeorder(const Order &order,int availablePoints, double availableCredit, QWidget *parent = nullptr);

signals:
    void orderCompleted(const Order &order);

private slots:
    void updatePreview();
    void onConfirm();

private:
    void setupUi();
    void fillTable();

    Order m_order;
    int m_availablePoints;
    double m_availableCredit;

    QTableWidget *m_table;
    QSpinBox *m_pointsSpin;
    QDoubleSpinBox *m_creditSpin;
    QLabel *m_subtotalLbl;
    QLabel *m_taxLbl;
    QLabel *m_finalLbl;
    QLabel *m_chargedLbl;
    QLabel *m_earnedLbl;
    QPushButton *m_confirmBtn;
};

#endif // COMPLETEORDER_H
