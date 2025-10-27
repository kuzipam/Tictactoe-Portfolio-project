#include<iostream>
#include<vector>
#include <string>
#include <limits>
using namespace std;

class Player {
protected:
    string name;
    char mark;

public:
    Player(string n, char m);

    string getName() const;
    char getMark() const;

    virtual void useAbility(char game_board[9]); 
};


class Alchemist : public Player{
    public:
    Alchemist(string n, char m);

    void useAbility(char game_board[9]);
};

bool adjacent(int spot1, int spot2);
class Paladin : public Player{
    public:
    Paladin(string n, char m);
    void useAbility(char game_board[9]);
};


void display_game_board(char game_board[9]);
void player_input(char player, char game_board[9]);
char check_winner(char game_board[9], const Player& p1, Player& p2);
bool check_winner(char game_board[9]);
int find_optimal_move(char game_board[9], char player, char bot);
int random_move(char game_board[9], int optimal);
void bot_moves(char game_board[9], char player, char bot, int diff_choice);