#ifndef SYSTEMDATA_H
#define SYSTEMDATA_H

#include "menu.h"
#include "orderqueue.h"
#include "user.h"
#include <memory>
#include <vector>

// Holds all in-memory data objects. Everything is rebuilt from the defaults every
// time the program starts (no database / file persistence in Deliverable 1).
class SystemData {
public:
    SystemData();

    void addUser(std::unique_ptr<User> user);
    const std::vector<std::unique_ptr<User>> &users() const { return m_users; }

    // Matches the entered text against username OR full name (case-insensitive).
    User *findUser(const QString &nameOrUsername) const;

    Menu &menu() { return m_menu; }
    const Menu &menu() const { return m_menu; }
    OrderQueue &orderQueue() { return m_queue; }

    int nextOrderNumber() { return m_nextOrderNumber++; }
    void setNextOrderNumber(int n) { m_nextOrderNumber = n; }

private:
    std::vector<std::unique_ptr<User>> m_users;
    Menu m_menu;
    OrderQueue m_queue;          // empty at startup
    int m_nextOrderNumber = 1001;
};

#endif // SYSTEMDATA_H
