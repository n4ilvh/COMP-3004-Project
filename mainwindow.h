#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "systemdata.h"
#include "useridentificationcontrol.h"
#include <QList>
#include <QMainWindow>

class QStackedWidget;
class LoginWidget;
class RoleHomeWidget;
class FeaturePage;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onLoginRequested(const QString &nameOrUsername);
    void onExitRequested();
    void showRoleHome();

private:
    void addFeaturePage(const QString &buttonText, FeaturePage *page);

    SystemData m_data;                       // all in-memory data (declared first)
    UserIdentificationControl m_idControl;
    QStackedWidget *m_stack;
    LoginWidget *m_login;
    RoleHomeWidget *m_roleView = nullptr;
    User *m_currentUser = nullptr;
    QList<FeaturePage *> m_featurePages;     // deleted on Exit
};

#endif // MAINWINDOW_H
