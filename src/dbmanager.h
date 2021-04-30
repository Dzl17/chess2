#ifndef CHESS2_DBMANAGER_H
#define CHESS2_DBMANAGER_H

#include <sqlite3.h>
#include "user.h"
#include <string>

using namespace std;

class DBManager {
private:
    sqlite3 *db{};
public:
    explicit DBManager(char *database);
    ~DBManager();

    User validateUser(char* username, char* password);

    void addUser(User user);

    void updateUserData(User user);

};


#endif
