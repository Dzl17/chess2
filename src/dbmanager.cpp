#include <cstring>
#include <iostream>
#include "dbmanager.h"

DBManager::DBManager(char *database) {
    int result = sqlite3_open(database, &this->db);
    if (result != SQLITE_OK) {
        std::cout << "DB ERROR" << std::endl;
    }
}

DBManager::~DBManager() {
    sqlite3_close(this->db);
}

User* DBManager::loadUser(char* username, char* password){
    sqlite3_stmt *stmt;
    int rc;

    char sql1[] = "SELECT username, elo, wins, losses, user_id FROM USER WHERE username=? AND password=?"; // Sentencia SQL

    // Preparar y ejecutar consulta 1
    rc = sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL); // TODO gestionar posibles errores
    if (rc != SQLITE_OK) std::cout << "PREPARE 1 ERROR" << std::endl;

    rc = sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC); // Introducir username
    if (rc != SQLITE_OK) std::cout << "BIND 1 ERROR" << std::endl;
    rc = sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC); // Introducir password
    if (rc != SQLITE_OK) std::cout << "BIND 2 ERROR" << std::endl;

    rc = sqlite3_step(stmt); // Ejecutar query
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) std::cout << "STEP 1 ERROR" << std::endl;

    // Sacar datos de la consulta 1
    char *temp_username = (char *) sqlite3_column_text(stmt, 0);
    int temp_elo = sqlite3_column_int(stmt, 1);
    int temp_wins = sqlite3_column_int(stmt, 2);
    int temp_losses = sqlite3_column_int(stmt, 3);
    int temp_id = sqlite3_column_int(stmt, 4);


    char sql2[] = "SELECT formation FROM FORMS WHERE user_id=?";

    // Preparar y ejecutar consulta 2
    rc = sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE 2 ERROR" << std::endl;

    rc = sqlite3_bind_int(stmt, 1, temp_id);
    if (rc != SQLITE_OK) std::cout << "BIND 3 ERROR" << std::endl;

    char **forms = new char*[4];
    for (int i = 0; i < 4; i++) forms[i] = new char[21];
    int i = 0;
    do {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) break; // Si se acaba la consulta
        strncpy(forms[i], (char*) sqlite3_column_text(stmt, 0), 21); // Copiar formación
        i++;
    } while (rc == SQLITE_ROW);
    if (i < 4) { // Rellenar formaciones inexistentes (debe haber 4)
        char emptyForm[21] = {'e','e','e','e','e','e','e','e','e','N','e','e','e','e','e','e','e','e','e','e','e'};
        for (int j = i; j < 4; j++) strncpy(forms[i], emptyForm, 21);
    }
    sqlite3_finalize(stmt);
    return new User(temp_username, temp_elo, temp_wins, temp_losses, forms);
}

void DBManager::addNewUser(char* username, char* password){
    sqlite3_stmt *stmt;
    int rc;

    // Usuario
    char sql1[] = "insert into USER values (?,?,?,0,0,0)";
    rc = sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE 1 ERROR" << std::endl;

    int newUserId = this->getHighestUserId() + 1;
    rc = sqlite3_bind_int(stmt, 1, newUserId);
    if (rc != SQLITE_OK) std::cout << "BIND 1 ERROR" << std::endl;
    rc = sqlite3_bind_text(stmt,2,username,strlen(username),SQLITE_STATIC);
    if (rc != SQLITE_OK) std::cout << "BIND 2 ERROR" << std::endl;
    rc = sqlite3_bind_text(stmt,3,password,strlen(password),SQLITE_STATIC);
    if (rc != SQLITE_OK) std::cout << "BIND 3 ERROR" << std::endl;

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) std::cout << "STEP 1 ERROR" << std::endl;

    // Formaciones
    char emptyForm[21] = {'e','e','e','e','e','e','e','e','e','N','e','e','e','e','e','e','e','e','e','e','e'};
    for (int i = 0; i < 4; ++i) {
        char sql2[] = "INSERT INTO FORMS VALUES (?,?,?)";

        rc = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
        if (rc != SQLITE_OK) std::cout << "PREPARE 2 ERROR" << std::endl;

        rc = sqlite3_bind_int(stmt, 1, getHighestFormId() + 1);
        if (rc != SQLITE_OK) std::cout << "BIND 4 ERROR" << std::endl;
        rc = sqlite3_bind_text(stmt, 2, emptyForm, strlen(emptyForm),SQLITE_STATIC);
        if (rc != SQLITE_OK) std::cout << "BIND 5 ERROR" << std::endl;
        rc = sqlite3_bind_int(stmt, 3, newUserId);
        if (rc != SQLITE_OK) std::cout << "BIND 6 ERROR" << std::endl;

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) std::cout << "STEP 2 ERROR" << std::endl;
    }
    sqlite3_finalize(stmt);
}

void DBManager::updateUserData(User user){
    sqlite3_stmt *stmt;
    int rc;

    // Usuario
    char sql1[] = "UPDATE USER SET elo=?, wins=?, losses=? WHERE username=?";
    rc = sqlite3_prepare_v2(db, sql1, strlen(sql1) + 1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE 1 ERROR" << std::endl;

    rc = sqlite3_bind_int(stmt, 1, user.getElo());
    if (rc != SQLITE_OK) std::cout << "BIND 1 ERROR" << std::endl;
    rc = sqlite3_bind_int(stmt, 2, user.getWins());
    if (rc != SQLITE_OK) std::cout << "BIND 2 ERROR" << std::endl;
    rc = sqlite3_bind_int(stmt, 3, user.getLosses());
    if (rc != SQLITE_OK) std::cout << "BIND 3 ERROR" << std::endl;
    rc = sqlite3_bind_text(stmt, 4, user.getUsername(), strlen(user.getUsername()),SQLITE_STATIC);
    if (rc != SQLITE_OK) std::cout << "BIND 4 ERROR" << std::endl;

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) std::cout << "STEP 1 ERROR" << std::endl;

    //Formaciones
    char sql2[] = "SELECT form_id FROM FORMS WHERE user_id = (SELECT user_id FROM USER WHERE username=?)";

    rc = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE 2 ERROR" << std::endl;

    rc = sqlite3_bind_text(stmt, 1, user.getUsername(), strlen(user.getUsername()), SQLITE_STATIC);
    if (rc != SQLITE_OK) std::cout << "BIND 5 ERROR" << std::endl;

    int *idBuffer = new int[4];
    int i = 0;
    do {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) break;
        idBuffer[i] = sqlite3_column_int(stmt, 0);
        i++;
    } while (rc == SQLITE_ROW);

    for (i = 0; i < 4; i++) {
        char sql3[] = "update FORMS set formation=? where form_id=?";

        rc = sqlite3_prepare_v2(db, sql3, strlen(sql3) + 1, &stmt, NULL);
        if (rc != SQLITE_OK) std::cout << "PREPARE 3 ERROR" << std::endl;

        rc = sqlite3_bind_text(stmt, 1, user.getForms()[i + 4], strlen(user.getForms()[i + 4]), SQLITE_STATIC);
        if (rc != SQLITE_OK) std::cout << "BIND 6 ERROR" << std::endl;

        rc = sqlite3_bind_int(stmt, 2, idBuffer[i]);
        if (rc != SQLITE_OK) std::cout << "BIND 7 ERROR" << std::endl;

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_ROW && rc != SQLITE_DONE) std::cout << "STEP 2 ERROR" << std::endl;
    }
    sqlite3_finalize(stmt);
    delete idBuffer;
}

bool DBManager::userExists(char *username) {
    sqlite3_stmt *stmt;
    int rc;

    char sql[] = "SELECT user_id FROM USER WHERE username=?"; // Sentencia SQL

    // Preparar y ejecutar consulta
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE ERROR" << std::endl;

    rc = sqlite3_bind_text(stmt,1,username,strlen(username),SQLITE_STATIC);
    if (rc != SQLITE_OK) std::cout << "BIND ERROR" << std::endl;

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) std::cout << "STEP ERROR" << std::endl;
    sqlite3_finalize(stmt);
    return rc == SQLITE_ROW;
}

int DBManager::getHighestUserId()
{
    sqlite3_stmt *stmt;
    int rc;

    char sql[] = "SELECT user_id FROM USER WHERE user_id = (SELECT MAX(user_ID) FROM USER)"; // Sentencia SQL

    // Preparar y ejecutar consulta
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE ERROR" << std::endl;

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) std::cout << "STEP ERROR" << std::endl;

    int value = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return value;
}

int DBManager::getHighestFormId()
{
    sqlite3_stmt *stmt;
    int rc;

    char sql[] = "SELECT form_id FROM FORMS WHERE form_id = (SELECT MAX(form_ID) FROM FORMS)";

    // Preparar y ejecutar consulta
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) std::cout << "PREPARE ERROR" << std::endl;

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) std::cout << "STEP ERROR" << std::endl;

    int value = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return value;
}