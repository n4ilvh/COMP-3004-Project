#ifndef ROLEHOMEWIDGET_H
#define ROLEHOMEWIDGET_H

#include <QWidget>

class QVBoxLayout;
class User;

// Boundary class: the screen shown after a user is identified.
// Header shows the user type and name plus an Exit button (same place for every role).
// Customer / Kitchen teammates add their feature widgets into featureLayout().
// Cashier / Manager / Admin leave it empty (only type + name are displayed).
class RoleHomeWidget : public QWidget {
    Q_OBJECT
public:
    explicit RoleHomeWidget(User *user, QWidget *parent = nullptr);
    QVBoxLayout *featureLayout() const { return m_featureLayout; }
    User *user() const { return m_user; }

signals:
    void exitRequested();

private:
    User *m_user;
    QVBoxLayout *m_featureLayout;
};

#endif // ROLEHOMEWIDGET_H
