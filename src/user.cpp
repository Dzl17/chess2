#include <iostream>
#include "user.h"

char* User::getUsername(){
    return this->username;
}
char* User::getPassword(){
    return this->password;
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
int User::getId(){
    return this->id;
}
void User::setId(int id){
    this->id=id;
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
void User::setForms(char** forms){
    this->forms= forms;
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