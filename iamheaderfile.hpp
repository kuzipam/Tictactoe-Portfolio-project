#include<iostream>
#include<vector>
#include <string>
#include <limits>
using namespace std;

class Player {
protected:
    string name;
    int health;
    int defense;
    int attack;
    char mark;

public:
    Player(string n, char m, int hp, int def, int atk);
    string getName() const;
    char getMark() const;
    virtual void useAbility(char game_board[9]);
    virtual string getplayerclass();
    int getHealth() const;
    int getAttack() const;
    int getDefense() const;
    void takeDamage(int amount);
    void heal(int amount);
    void modifyAttack(int delta);
    void modifyDefense(int delta);

};


class Alchemist : public Player{
    public:
    Alchemist(string n, char m, int hp, int def, int atk);

    void useAbility(char game_board[9]);
    string getplayerclass();
};

bool adjacent(int spot1, int spot2);
class Paladin : public Player{
    public:
    Paladin(string n, char m, int hp, int def, int atk);
    void useAbility(char game_board[9]);
    string getplayerclass();
};

class Bot{ 
    public:
    string name;
    int health;
    int defense;
    int attack;
    char mark;
    Bot(const string& n, int hp, int atk, int def, char m);
    
    virtual void useAbility(char game_board[9]); 
    int find_optimal_move(char game_board[9], char player, char bot);
    int random_move(char game_board[9], int optimal, char player, char bot);
    void bot_moves(char game_board[9], char player, char bot, int diff_choice);

};

char play_round(Player &player, Bot &enemy);
void battle(Player &player, Bot &enemy);
void display_game_board(char game_board[9]);
void player_input(char player, char game_board[9]);
char check_winner(char game_board[9], char p1mark, char p2mark);
void campaign(Player* p);   
void moralChoices(const string& enemyName, int &spared, int &executed);
void goodEnding(Player &player);
void badEnding(Player &player);
void neutralEnding(Player &player);


