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

    bool verifyUser(char* username, char* password);
    User* loadUser(char* username);
    void addNewUser(char* username, char* password);
    void updateUserData(User user);

    bool userExists(char *username);
    int getHighestUserId();
    int getHighestFormId();
};


#endif
