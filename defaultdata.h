#ifndef DEFAULTDATA_H
#define DEFAULTDATA_H

class SystemData;

namespace DefaultData {
// Loads the café menu (10 items), 11 users and 25 historical orders into memory.
void load(SystemData &data);
}

#endif // DEFAULTDATA_H
