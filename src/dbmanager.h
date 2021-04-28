#ifndef CHESS2_DBMANAGER_H
#define CHESS2_DBMANAGER_H

#include <sqlite3.h>

class DBManager {
private:
    sqlite3 *db{};
public:
    explicit DBManager(char *database);
    ~DBManager();
};


#endif
