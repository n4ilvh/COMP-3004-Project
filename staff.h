#ifndef STAFF_H
#define STAFF_H

#include "user.h"

class Staff : public User {
public:
    Staff(const QString &name, const QString &username, const QString &staffId)
        : User(name, username), m_staffId(staffId) {}
    const QString &staffId() const { return m_staffId; }

private:
    QString m_staffId;
};

class Kitchen : public Staff {
public:
    using Staff::Staff;
    QString userType() const override { return "Kitchen Staff"; }
};

class Cashier : public Staff {
public:
    using Staff::Staff;
    QString userType() const override { return "Cashier"; }
};

class Manager : public Staff {
public:
    using Staff::Staff;
    QString userType() const override { return "Manager"; }
};

class Admin : public Staff {
public:
    using Staff::Staff;
    QString userType() const override { return "System Administrator"; }
};

#endif // STAFF_H
