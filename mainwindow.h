#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "systemdata.h"
#include "useridentificationcontrol.h"
#include <QMainWindow>

class QStackedWidget;
class LoginWidget;
class RoleHomeWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onLoginRequested(const QString &nameOrUsername);
    void onExitRequested();

private:
    SystemData m_data;                       // all in-memory data (declared first)
    UserIdentificationControl m_idControl;
    QStackedWidget *m_stack;
    LoginWidget *m_login;
    RoleHomeWidget *m_roleView = nullptr;
    User *m_currentUser = nullptr;
};

#endif // MAINWINDOW_H
