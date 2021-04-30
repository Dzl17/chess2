#include <cstring>
#include "user.h"

char* User::getUsername(){
    return this->username;
}

int User::getElo(){
    return this->elo;
}
int User::getWins(){
    return this->wins;
}
int User::getLoses(){
    return this->loses;
}
char** User::getForms(){
    return this->forms;
}
void User::addWin(){
    this->wins++;
}
void User::addLose(){
    this->loses++;
}
void User::setForms(char **formArr){
    for (int i = 0; i < 4; i++) {
        strncpy(this->forms[i], formArr[i], 21);
    }
}
void User::calculateElo(int enemyRating,bool win){
    if (win){
        this->elo+=400+enemyRating;
    }
    else {
        this->elo-=400+enemyRating;
    }
    this->elo= this->elo/(wins+loses);
}

User::User(char *username, int elo, int wins, int loses, char **forms)
{
    this->username = username;
    this->elo = elo;
    this->wins = wins;
    this->loses = loses;
    this->forms = forms;
}
