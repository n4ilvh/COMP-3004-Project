#ifndef USERIDENTIFICATIONCONTROL_H
#define USERIDENTIFICATIONCONTROL_H

#include <QString>

class SystemData;
class User;

// Control class: verifies a typed name/username against the in-memory users.
// (User identification only - not true authentication.)
class UserIdentificationControl {
public:
    explicit UserIdentificationControl(const SystemData &data) : m_data(data) {}
    User *identify(const QString &nameOrUsername) const;

private:
    const SystemData &m_data;
};

#endif // USERIDENTIFICATIONCONTROL_H
