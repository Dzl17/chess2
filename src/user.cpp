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
    return this->forms.forms;
}
void User::addWin(){
    this->wins++;
}
void User::addLose(){
    this->loses++;
}
void User::setForms(char **formArr){
    for (int i = 0; i < 4; i++) {
        strncpy(this->forms.forms[i], formArr[i], 21);
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
    char** tempforms=new char*[8];
    for (int i = 0; i < 4; ++i) {
        char* meform=loadForm(i+1);
        strncpy(tempforms[i], meform, 21);
        free(meform);
    }
    for (int i = 4; i < 8; ++i) {
         strncpy(tempforms[i], forms[i], 21);
    }
    this->forms = {tempforms,8,0};
}
