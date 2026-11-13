#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "systemdata.h"
#include "useridentificationcontrol.h"
#include <QList>
#include <QMainWindow>
#include <memory>

class QStackedWidget;
class LoginWidget;
class RoleHomeWidget;
class FeaturePage;
class PlaceOrderControl;
class PlaceOrder;
class Customer;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginRequested(const QString &nameOrUsername);
    void onExitRequested();
    void showRoleHome();
    void showOrderDetails(int orderNumber);
    void completeQueuedOrder(int orderNumber);

private:
    Customer *findCustomer(const QString &username) const;
    void addFeaturePage(const QString &buttonText, FeaturePage *page);

    SystemData m_data;                       // all in-memory data (declared first)
    UserIdentificationControl m_idControl;
    QStackedWidget *m_stack;
    LoginWidget *m_login;
    RoleHomeWidget *m_roleView = nullptr;
    User *m_currentUser = nullptr;
    std::unique_ptr<PlaceOrderControl> m_ordering;
    PlaceOrder *m_checkout = nullptr;
    QList<FeaturePage *> m_featurePages;     // deleted on Exit
};

#endif // MAINWINDOW_H
