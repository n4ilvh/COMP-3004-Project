#include "useridentificationcontrol.h"
#include "systemdata.h"

User *UserIdentificationControl::identify(const QString &nameOrUsername) const
{
    return m_data.findUser(nameOrUsername);
}
