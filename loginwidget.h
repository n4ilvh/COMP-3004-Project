#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

class QLineEdit;
class QLabel;
class QPushButton;

// Boundary class: the startup form.
class LoginWidget : public QWidget {
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    void showError(const QString &message);
    void reset();                         // clears typed text and errors

signals:
    void loginRequested(const QString &nameOrUsername);

private slots:
    void onLoginClicked();

private:
    QLineEdit *m_input;
    QLabel *m_error;
    QPushButton *m_loginButton;
};

#endif // LOGINWIDGET_H
