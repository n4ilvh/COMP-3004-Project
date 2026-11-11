#include "mainwindow.h"
#include "loginwidget.h"
#include "rolehomewidget.h"
#include "customer.h"
#include "staff.h"
#include <QStackedWidget>
#include "viewmenu.h"
#include "featurepage.h"
#include "viewdashboard.h"
#include "viewqueue.h"
#include <QVBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_idControl(m_data)
{
    setWindowTitle("DragonEndPOS");
    resize(900, 600);

    m_stack = new QStackedWidget(this);
    m_login = new LoginWidget(this);
    m_stack->addWidget(m_login);
    setCentralWidget(m_stack);

    connect(m_login, &LoginWidget::loginRequested, this, &MainWindow::onLoginRequested);
}

void MainWindow::onLoginRequested(const QString &nameOrUsername)
{
    User *user = m_idControl.identify(nameOrUsername);
    if (!user) {
        m_login->showError("User not found. Please check your name or username.");
        return;
    }

    m_currentUser = user;
    m_roleView = new RoleHomeWidget(user, this);
    connect(m_roleView, &RoleHomeWidget::exitRequested, this, &MainWindow::onExitRequested);

    // ---- Teammates: add role-specific features here -------------------------
    // Only Customer and Kitchen Staff get features. Cashier, Manager and
    // Administrator show just their user type and name.
    if (auto *customer = dynamic_cast<Customer *>(user)) {
        Q_UNUSED(customer)

        addFeaturePage("View Menu", new viewMenu(m_data));

        // Feature 4: View Customer Online Dashboard
        addFeaturePage("View Dashboard", new ViewDashboard(*customer));

    // e.g. m_roleView->featureLayout()->addWidget(new CustomerPanel(customer, &m_data));
    } else if (auto *kitchen = dynamic_cast<Kitchen *>(user)) {
        Q_UNUSED(kitchen)

        // Feature 5: View Order Queue
        auto *queueView = new ViewQueue(m_data.orderQueue());
        addFeaturePage("View Order Queue", queueView);
        // features 6 and 7: connect queueView's viewDetailsRequested / completeOrderRequested here
    }
    // --------------------------------------------------------------------------

    m_stack->addWidget(m_roleView);
    m_stack->setCurrentWidget(m_roleView);
}

void MainWindow::addFeaturePage(const QString &buttonText, FeaturePage *page)
{
    auto *button = new QPushButton(buttonText, m_roleView);
    m_roleView->featureLayout()->addWidget(button);

    m_stack->addWidget(page);
    m_featurePages.append(page);

    connect(button, &QPushButton::clicked, this, [this, page] { m_stack->setCurrentWidget(page); });
    connect(page, &FeaturePage::backRequested, this, &MainWindow::showRoleHome);
}

void MainWindow::showRoleHome()
{
    if (m_roleView)
        m_stack->setCurrentWidget(m_roleView);
}

void MainWindow::onExitRequested()
{
    // Destroy the previous user's screen and clear the form so nothing carries over.
    m_stack->setCurrentWidget(m_login);
    for (FeaturePage *page : m_featurePages) {
        m_stack->removeWidget(page);
        page->deleteLater();
    }
    m_featurePages.clear();
    if (m_roleView) {
        m_stack->removeWidget(m_roleView);
        m_roleView->deleteLater();
        m_roleView = nullptr;
    }
    m_currentUser = nullptr;
    m_login->reset();
}
