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

    User loadUser(char* username, char* password);
    void addNewUser(char* username, char* password);
    void updateUserData(User user);

    int getHighestUserId();
    int getHighestFormId();
};


#endif
