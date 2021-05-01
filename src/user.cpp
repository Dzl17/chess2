#include <cstring>
#include <cstdlib>
#include <iostream>
#include "user.h"
extern "C" {
    #include "game/filem.h"
}

char* User::getUsername(){
    return this->username;
}

int User::getElo() const{
    return this->elo;
}

int User::getWins() const{
    return this->wins;
}

int User::getLoses() const{
    return this->loses;
}

char** User::getForms() const{
    return this->formationSet.forms;
}

void User::addWin(){
    this->wins++;
}

void User::addLose(){
    this->loses++;
}

void User::setForms(char **formArr) const{
    for (int i = 0; i < 4; i++) {
        strncpy(this->formationSet.forms[i], formArr[i], 21);
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
    char** tempforms = new char*[8];
    for (int i = 0; i < 8; i++) tempforms[i] = new char[FORM_LENGTH];
    for (int i = 0; i < 4; i++) {
        char* meform = loadForm(i+1);
        strncpy(tempforms[i], meform, FORM_LENGTH);
        free(meform);
    }
    for (int i = 4; i < 8; ++i) {
        strncpy(tempforms[i], forms[i-4], 21);
    }
    this->formationSet = {tempforms,8,0};
    delete forms;
}
