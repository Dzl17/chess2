#ifndef CHESS2_USER_H
#define CHESS2_USER_H


class User {
private:
    char* username;
    char* password;
    int elo, wins, loses,id;
    char **forms;
public:
    char* getUsername();
    char* getPassword();
    int getElo();
    int getId();
    int getWins();
    int getLoses();
    char** getForms();
    void addWin();
    void addLose();
    void setForms(char** form);
    void setId(int id);
    void calculateElo(int enemyRating,bool win);

    User(char* username, char* password,int elo, int wins, int loses, char** forms){
        this->username=username;
        this->password=password;
        this->elo=elo;
        this->wins=wins;
        this->loses=loses;
        this->forms=forms;
    }
};


#endif //CHESS2_USER_H
