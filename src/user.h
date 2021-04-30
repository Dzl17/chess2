#ifndef CHESS2_USER_H
#define CHESS2_USER_H


class User {
private:
    char* username;
    int elo, wins, loses;
    char **forms;
public:
    char* getUsername();
    int getElo();
    int getWins();
    int getLoses();
    char** getForms();
    void addWin();
    void addLose();
    void setForms(char** form);
    void calculateElo(int enemyRating,bool win);

    User(char* username, int elo, int wins, int loses, char** forms);
};


#endif //CHESS2_USER_H
