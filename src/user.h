#ifndef CHESS2_USER_H
#define CHESS2_USER_H


#include "content.h"

class User {
private:
    char* username;
    int elo, wins, loses;
    FormationSet forms;
public:
    char* getUsername();
    int getElo();
    int getWins();
    int getLoses();
    char** getForms();
    void addWin();
    void addLose();
    void setForms(char** forms);
    void calculateElo(int enemyRating,bool win);

    User(char* username, int elo, int wins, int loses, char** forms);
};


#endif //CHESS2_USER_H
