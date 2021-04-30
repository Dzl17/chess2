#include <cstring>
#include <iostream>
#include "dbmanager.h"

DBManager::DBManager(char *database) {
    sqlite3_open(database, &this->db);
}

DBManager::~DBManager() {
    sqlite3_close(this->db);
}

User DBManager::validateUser(char* username, char* password){
    sqlite3_stmt *stmt;
    char sql[]="select * from USER where username=? and password=?";
    int result =sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    result= sqlite3_bind_text(stmt,1,username,strlen(username),SQLITE_STATIC);
    result= sqlite3_bind_text(stmt,2,password,strlen(password),SQLITE_STATIC);
    char **forms = (char**)malloc(4*sizeof(char*));
    User user = User(nullptr, nullptr, 0, 0, 0, forms);
    if (result == SQLITE_OK){
        result = sqlite3_step(stmt) ;
        user=User((char *) sqlite3_column_text(stmt, 1),(char *) sqlite3_column_text(stmt, 2),
                  sqlite3_column_int(stmt, 3),sqlite3_column_int(stmt, 4),sqlite3_column_int(stmt, 5),
                  nullptr);
        user.setId(sqlite3_column_int(stmt, 0));
    }
    char sql1[]= "select * from FORMS where user_id=?";
    result =sqlite3_prepare_v2(db, sql1, -1, &stmt, NULL);
    result= sqlite3_bind_int(stmt,1,user.getId());
    char*formaciones;
    int i=0;
    if (result == SQLITE_OK){
        do  {
            result=sqlite3_step(stmt);
            if (result==SQLITE_ROW){
                formaciones= (char *) sqlite3_column_text(stmt, 1);
                forms[i]=formaciones;
                std::cout <<forms[i]<<std::endl;
                i++;
            }
        }while (result == SQLITE_ROW);
        user.setForms(forms);
    }
    return user;
}

void DBManager::addUser(User user){
    sqlite3_stmt *stmt;
    char sql[]="insert into USERS values (?,?,?,?,?,?)";
    int result =sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    result=sqlite3_bind_int(stmt,0,user.getId());
    result= sqlite3_bind_text(stmt,1,user.getUsername(),strlen(user.getUsername()),SQLITE_STATIC);
    result= sqlite3_bind_text(stmt,2,user.getPassword(),strlen(user.getUsername()),SQLITE_STATIC);
    result= sqlite3_bind_int(stmt,3,user.getElo());
    result= sqlite3_bind_int(stmt,4,user.getWins());
    result= sqlite3_bind_int(stmt,5,user.getLoses());
    result=sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    /*
    for (int i = 0; i < 4; ++i) {
    char sql1[]="insert into FORMS values (?,?,?)";
        result= sqlite3_bind_int(stmt,0,i);
        result= sqlite3_bind_text(stmt,1,user.getForms()[i],strlen(user.getForms()[i]),SQLITE_STATIC);
        result= sqlite3_bind_int(stmt,2,user.getId());
        result=sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    */
}

void updateUserData(sqlite3 *db, User user){

}