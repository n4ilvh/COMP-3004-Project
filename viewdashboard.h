#ifndef VIEWDASHBOARD_H
#define VIEWDASHBOARD_H

#include "dashboardcontrol.h"
#include "featurepage.h"

class Customer;
class QLabel;
class QStackedWidget;
class QTableWidget;

// Boundary class: the customer's online dashboard.
class ViewDashboard : public FeaturePage {
    Q_OBJECT
public:
    explicit ViewDashboard(Customer &customer, QWidget *parent = nullptr);

public slots:
    void refresh() override;

private slots:
    void editContactInfo();

private:
    QWidget *buildAccountBox();
    QWidget *buildCurrentOrderBox();
    QWidget *buildHistoryBox();
    void showAccount();
    void showCurrentOrder();
    void showHistory();

    DashboardControl m_control;

    QLabel *m_nameLabel = nullptr;
    QLabel *m_loyaltyNumberLabel = nullptr;
    QLabel *m_pointsLabel = nullptr;
    QLabel *m_creditLabel = nullptr;
    QLabel *m_emailLabel = nullptr;
    QLabel *m_addressLabel = nullptr;

    QStackedWidget *m_currentOrderStack = nullptr;   // page 0 = no order, page 1 = details
    QLabel *m_orderNumberLabel = nullptr;
    QLabel *m_orderStatusLabel = nullptr;
    QLabel *m_orderPlacedLabel = nullptr;
    QLabel *m_orderItemsLabel = nullptr;
    QLabel *m_orderFinalPriceLabel = nullptr;
    QLabel *m_orderChargedLabel = nullptr;
    QLabel *m_orderPointsUsedLabel = nullptr;
    QLabel *m_orderPointsEarnedLabel = nullptr;
    QLabel *m_orderCreditUsedLabel = nullptr;

    QTableWidget *m_historyTable = nullptr;
    QLabel *m_historyEmptyLabel = nullptr;
};

#endif // VIEWDASHBOARD_H
