#include "dbmanager.h"

DBManager::DBManager(char *database) {
    sqlite3_open(database, &this->db);
}

DBManager::~DBManager() {
    sqlite3_close(this->db);
}
