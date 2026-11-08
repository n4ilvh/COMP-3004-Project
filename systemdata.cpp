#include "systemdata.h"
#include "defaultdata.h"

SystemData::SystemData()
{
    DefaultData::load(*this);
}

void SystemData::addUser(std::unique_ptr<User> user)
{
    m_users.push_back(std::move(user));
}

User *SystemData::findUser(const QString &nameOrUsername) const
{
    const QString key = nameOrUsername.trimmed();
    if (key.isEmpty())
        return nullptr;

    for (const auto &u : m_users) {
        if (u->username().compare(key, Qt::CaseInsensitive) == 0)
            return u.get();
    }
    for (const auto &u : m_users) {
        if (u->name().compare(key, Qt::CaseInsensitive) == 0)
            return u.get();
    }
    return nullptr;
}
