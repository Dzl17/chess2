#ifndef CHESS2_USER_H
#define CHESS2_USER_H

typedef struct {
    char **forms;
    int size, index;
} FormationSet;

class User {
private:
    char* username;
    int elo, wins, losses;
public:
    FormationSet formationSet = {};

    char* getUsername();
    int getElo() const;
    int getWins() const;
    int getLosses() const;
    char** getForms() const;

    void addWin();
    void addLose();
    void setForms(char** forms) const;
    void calculateElo(int enemyRating,bool win);

    User(char* username, int elo, int wins, int loses, char** forms);
};


#endif //CHESS2_USER_H
