#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    User(const QString &name, const QString &username);
    virtual ~User() = default;

    const QString &name() const { return m_name; }
    const QString &username() const { return m_username; }
    virtual QString userType() const = 0;   // "Customer", "Kitchen Staff", ...

private:
    QString m_name;
    QString m_username;
};

#endif // USER_H
