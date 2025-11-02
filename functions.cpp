#include<iostream>
#include<vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "iamheaderfile.hpp"

using namespace std;

void display_game_board(char game_board[9]){
    //Displaying the array as tictactoe board using ASCII art.
    std::cout << game_board[0] << "   |  " << game_board[1] << " |  " << game_board[2] << '\n'
              << "----+----+----\n"
              << game_board[3] << "   |  " << game_board[4] << " |  " << game_board[5] << '\n'
              << "----+----+----\n"
              << game_board[6] << "   |  " << game_board[7] << " |  " << game_board[8] << '\n';

}

void player_input(char player, char game_board[9]) {
//Player input function that takes input from the players as single characters 'X' and 'O'
    char input;
    int choice = 0;
    int index = 0;
    
    //Updated the function and other varibles that require user user input to handle invalid inputs with out crashing the program.
    while (true){
    
        std::cout << "\nPlayer '" << player << "' pick where you want to play between 1-9: \n"; 
        std::cin >> input;
        std::cin.ignore(1000, '\n'); 

        //Checking if the input is a digit.
        if (!isdigit(input)){
            cout << "Invalid input! Please enter a number.";
            continue;
        }
        //Storing the difference of the input and '0' as an integer.
        choice = input - '0';

        //This handles the range of the inputs.
        while (choice < 1 || choice > 9)
        {
            std::cout << "Please choose Between 1-9. Try again\n";   
            std::cin >> choice;
            continue;
        }

        index = choice - 1;

        //Changed the player input function to work with different marks instead of being hardcoded to work with only X and O.
        if (isdigit(game_board[index])) {
            game_board[index] = player;
            break;
        } else {
            std::cout << "That spot is already taken. Try again.\n";
        }

    }
} 

//Function that checks for a winner or draw at the end of the game.
bool check_winner(char game_board[9]) {

    //This checks for Row wins.
    if (game_board[0] == game_board[1] && game_board[1] == game_board[2]) return game_board[0];
    if (game_board[3] == game_board[4] && game_board[4] == game_board[5]) return game_board[3];
    if (game_board[6] == game_board[7] && game_board[7] == game_board[8]) return game_board[6];

    //This checks for Column wins.
    if (game_board[0] == game_board[3] && game_board[3] == game_board[6]) return game_board[0];
    if (game_board[1] == game_board[4] && game_board[4] == game_board[7]) return game_board[1];
    if (game_board[2] == game_board[5] && game_board[5] == game_board[8]) return game_board[2];

    //This shecks for Diagonal wins.
    if (game_board[0] == game_board[4] && game_board[4] == game_board[8]) return game_board[0];
    if (game_board[2] == game_board[4] && game_board[4] == game_board[6]) return game_board[2];

    //This checks for a draw. If there is an empty space the full variable is set to false and the game continues.
    bool full = true;

    for(int i = 0; i < 9; i++){

        if(game_board[i] != 'X' && game_board[i] != 'O'){
            full = false;
            break; 
        }
    }
    if (full) return 'D';

    //This returns empty so the much can continue if there isnt a winner yet.
    return ' '; 
}

//Overloading function to work with the new player class and marks.
char check_winner(char game_board[9], const Player& p1, Player& p2) {
    char a = p1.getMark();
    char b = p2.getMark();

    //This checks for Row wins.
    if (game_board[0] == game_board[1] && game_board[1] == game_board[2]) return game_board[0];
    if (game_board[3] == game_board[4] && game_board[4] == game_board[5]) return game_board[3];
    if (game_board[6] == game_board[7] && game_board[7] == game_board[8]) return game_board[6];

    //This checks for Column wins.
    if (game_board[0] == game_board[3] && game_board[3] == game_board[6]) return game_board[0];
    if (game_board[1] == game_board[4] && game_board[4] == game_board[7]) return game_board[1];
    if (game_board[2] == game_board[5] && game_board[5] == game_board[8]) return game_board[2];

    //This shecks for Diagonal wins.
    if (game_board[0] == game_board[4] && game_board[4] == game_board[8]) return game_board[0];
    if (game_board[2] == game_board[4] && game_board[4] == game_board[6]) return game_board[2];

    //This checks for a draw. If there is an empty space the full variable is set to false and the game continues.
    bool full = true;

    for(int i = 0; i < 9; i++){

        if(game_board[i] != a && game_board[i] != b){
            full = false;
            break; 
        }
    }
    if (full) return 'D';

    //This returns empty so the much can continue if there isnt a winner yet.
    return ' '; 
}

//This function uses the moves from the Wikipedia link to find the most optimal move on the board that the bot can use.
int find_optimal_move(char game_board[9], char player, char bot) {

    //Using a loop for the bot to go through all the empty spaces to look for a winning move.  
    for (int i = 0; i < 9; i++) {

        if (game_board[i] != 'X' && game_board[i] != 'O') {

            char backup = game_board[i];
            game_board[i] = bot;

            if (check_winner(game_board) == bot) {
                game_board[i] = backup;
                return i;
            }
            game_board[i] = backup;
        }
    }

    //This does the same as the previous loop but the bot looks for an empty space that will block the player from winning.
    for (int i = 0; i < 9; i++) {

        if (game_board[i] != 'X' && game_board[i] != 'O') {

            char backup = game_board[i];
            game_board[i] = player;
            
            if (check_winner(game_board) == player) {
                game_board[i] = backup;
                return i;
            }
            game_board[i] = backup;
        }
    }

    //The bot takes the centre if its free.
    if (game_board[4] != 'X' && game_board[4] != 'O') return 4;

    //The bots takes the opposite corner from the player if its free.
    if (game_board[0] == player && game_board[8] == 'X') return 8;
    if (game_board[8] == player && game_board[0] == 'X') return 0;
    if (game_board[2] == player && game_board[6] == 'X') return 6;
    if (game_board[6] == player && game_board[2] == 'X') return 2;

    //The bots takes any corner if its free.
    int corners[4] = {0, 2, 6, 8};

    for (int i = 0; i < 4; i++) {

        if (game_board[corners[i]] != 'X' && game_board[corners[i]] != 'O') return corners[i];
    }

    //The bot takes any side spot if its free too.
    int sides[4] = {1, 3, 5, 7};

    for (int i = 0; i < 4; i++) {

        if (game_board[sides[i]] != 'X' && game_board[sides[i]] != 'O') return sides[i];
    }

    //The bots doesnt have any moves to make.
    return -1; 
}

//Picks a random move that is NOT the optimal one
int random_move(char game_board[9], int optimal) {

    std::vector<int> bot_choices;

    for (int i = 0; i < 9; i++) {

        if (game_board[i] != 'X' && game_board[i] != 'O' && i != optimal) {
            bot_choices.push_back(i);
        }
    }

    //Check to see if the vector that stores the random moves is empty. If it is empty then the bot just plays the optimal move.
    if (bot_choices.empty()) return optimal; 

    //Using rand to generate a random move that the bot plays.
    int r = rand() % bot_choices.size();
    return bot_choices[r];
}

//This is the function that handles the execution of the bot moves.
void bot_moves(char game_board[9], char player, char bot, int diff_choice) {

    //Calling the optimal move function to look for the best moves that can be played.
    int optimal = find_optimal_move(game_board, player, bot);
    int move = optimal;
    

    //Using switch cases to set the bots difficulty. The user inputs the difficulty they would like to play against and the error chance is set for each difficulty.
    int errorChance = 0;

    switch (diff_choice) {
        case 1: errorChance = 75; break; //Easy
        case 2: errorChance = 30; break; //Medium
        case 3: errorChance = 10; break; //Hard
        case 4: errorChance = 0;  break; //Impossible
    }

    //Using rand to sort of roll a dice to decide if the bot should make an error or not.
    int random_dice = rand() % 100;

    if (random_dice < errorChance) {

        //Random move function is called if the the bot does make an error.
        move = random_move(game_board, optimal);
    }

    //The bot makes its move. Since the bot returns -1 in the optimal move function if it doesnt find a move, I used it as a condition to avoid any errors.
    if (move != -1 && game_board[move] != 'X' && game_board[move] != 'O') {
        game_board[move] = bot;
    }
}

Player::Player(string n, char m)
    : name(n), mark(m) {}

string Player::getName() const {
    return name;
}

char Player::getMark() const {
    return mark;
}

void Player::useAbility(char game_board[9]){}


Alchemist:: Alchemist(string n, char m) : Player(n, m){};

void Alchemist::useAbility(char game_board[9]) {
    int marks = 0;

    //Count all of the player's marks on the board.
    for (int i = 0; i < 9; i++) {
        if (game_board[i] == getMark()) {
            marks++;
        }
    }

    //Checks for at least two marks
    if (marks < 2) {
        std::cout << name << ", you need at least 2 of your marks on the game board to use your special ability.\n";
        std::cout << "Make a regular move instead.\n";
        player_input(getMark(), game_board);  
        return;
    }

    int spot1 = 0;
    int spot2 = 0;

    std::cout << name << ", you are an Alchemist. Please select two different positions to swap (1-9).\n";
    std::cout << "Spot 1: ";
    std::cin >> spot1;
    std::cout << "Spot 2: ";
    std::cin >> spot2;

    while (spot1 < 1 || spot1 > 9 || spot2 < 1 || spot2 > 9) {
        std::cout << "Invalid input! Please try entering two different numbers (1-9): ";
        std::cin >> spot1 >> spot2;
    }

    if (game_board[spot1 - 1] == game_board[spot2 - 1]) {
        std::cout << "These spots have the same marks. Nothing swapped.\n";
        return;
    }

    std::swap(game_board[spot1 - 1], game_board[spot2 - 1]);
    std::cout << "Swap complete!\n";
}


Paladin::Paladin(string n, char m) : Player(n, m){};


bool adjacent(int spot1, int spot2) {
    
    int row_spot1 = (spot1 - 1) / 3;
    int col_spot1 = (spot1 - 1) % 3;
    int row_spot2   = (spot2 - 1) / 3;
    int col_spot2   = (spot2- 1) % 3;

    return abs(row_spot1- row_spot2) <= 1 && abs(col_spot1 - col_spot2) <= 1;
}

void Paladin::useAbility(char game_board[9]) {
    bool hasMark = false;

    //Check if the player has at least one mark
    for (int i = 0; i < 9; i++) {
        if (game_board[i] == getMark()) {
            hasMark = true;
            break;
        }
    }

    if (!hasMark) {
        std::cout << name << ", you need at least 1 mark on the game board to use your special ability.\n";
        std::cout << "Make a regular move instead.\n";
        player_input(getMark(), game_board); 
        return;
    }

    int spot1 = 0;
    int spot2 = 0;

    std::cout << name << ", you are a Paladin. Move one of your marks to an adjacent empty spot.\n";
    std::cout << "Move from: ";
    std::cin >> spot1;

    while (std::cin.fail() || spot1 < 1 || spot1 > 9 || game_board[spot1 - 1] != getMark()) {
        std::cout << "Invalid input! Please try entering a valid number (1-9): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> spot1;
    }

    std::cout << "Move to: ";
    std::cin >> spot2;

    while (std::cin.fail() || spot2 < 1 || spot2 > 9 ||!adjacent(spot1, spot2) ||game_board[spot2 - 1] == 'X' || game_board[spot2 - 1] == 'O'){
        std::cout << "Invalid input! Please choose an adjacent empty cell (1-9): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> spot2;
    }

    std::swap(game_board[spot1 - 1], game_board[spot2 - 1]);
    std::cout << "Move complete!\n";
}
