#include<iostream>
#include<vector>
#include "iamheaderfile.hpp"
#include <cstdlib>
#include <ctime>

#include <limits>

using namespace std;

int main() {
    srand(time(0));
    int choice = 0;

    //Creating the game board.
    char game_board[9] = {'1','2','3','4','5','6','7','8','9'};
    while (choice != 1 && choice != 2 && choice != 3) {

        std::cout << "Would you like to play against another player or a bot?\n"
                  << "Enter 1 to play against another player.\nEnter 2 to play against a bot.\nEnter 3 to play battle tictactoe with another player.\n";

        std::cin >> choice;

        if (!std::cin) {

            std::cout << "Invalid input! Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n'); 
            choice = 0; 

        } else if (choice != 1 && choice != 2 && choice != 3) {
        std::cout << "Invalid choice! Please enter 1 or 2.\n";

        }
    }

    //If the player chooses option 1, they play against someone else.
    if (choice == 1){

        //Creating player instances
        char mark_p1;
        string name_p1;

        char mark_p2;
        string name_p2;

        cout << "Player 1 please enter your name: ";
        getline(cin >> ws, name_p1);

        while (name_p1.empty()) {
            cout << "Name cannot be empty. Please enter your name: ";
            getline(cin >> ws, name_p1);
        }

        cout << "Hello " << name_p1 << " please choose your player mark: ";
        cin >> mark_p1;

        while (mark_p1 == ' ' || !isprint(mark_p1) || isdigit(mark_p1)) {
            cout << "Invalid entry! Please choose a valid symbol that isn't a number or space: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> mark_p1;
        }

        Player player1(name_p1, mark_p1);

        cout << "Player 2 please enter your name: ";
        getline(cin >> ws, name_p2);

        while (name_p2.empty()) {
            cout << "Name cannot be empty. Please enter your name: ";
            getline(cin >> ws, name_p2);
        }


        cout << "Hello " << name_p2 << " please choose your player mark: ";
        cin >> mark_p2;

        while (mark_p1 == mark_p2 || mark_p2 == ' ' || !isprint(mark_p2) || isdigit(mark_p2)){
            cout << "Invalid entry! Please choose a valid symbol that isn't a number or empty space: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> mark_p2;
        }

        Player player2(name_p2, mark_p2);

        Player* current_player = &player1;

        while(true){
            //Displaying game board
            display_game_board(game_board);
            cout << "\n\n";

            cout << current_player -> getName() <<" its your turn to play. (" << current_player->getMark() <<") \n";

            //Calling player input function so player can play.
            player_input(current_player->getMark(), game_board);

            //Showing updated game board after a move is made.
            cout << "\n\n";
            display_game_board(game_board);

            //Checking for winner after every valid move is made.
            char winner = check_winner(game_board, player1, player2);
            if(winner == current_player->getMark()){
                cout << current_player->getName()<< " wins this round!";
                break;

            } else if(winner == 'D'){cout << "This rounds ends in a draw!"; break;}

            //Switching players.
            current_player = (current_player == &player1) ? &player2 : &player1;
        }


     //If not they play against a bot.
    } else if( choice == 2) {
        int difficulty = 0;
        while (difficulty < 1 || difficulty > 4) {
            std::cout << "Please select the bot difficulty to start the game.\n"
                      << "1. Easy\n"
                      << "2. Medium\n"
                      << "3. Hard\n"
                      << "4. Impossible\n";

            std::cin >> difficulty;

            if (!std::cin) {
                
                std::cout << "Invalid input! Please enter a number.\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n'); 
                difficulty = 0;

            } else if (difficulty < 1 || difficulty > 4) {
                std::cout << "Invalid choice! Please enter between 1 and 4.\n";
            }
        }

    while (true) {
    
        display_game_board(game_board);

        char player = 'X';
        char bot = 'O';

        player_input(player, game_board);
        display_game_board(game_board);
        cout << "\n\n\n";

        char winner = check_winner(game_board);
        if (winner == 'X') {
            cout << "Player X wins!\n";
            break;
        } else if (winner == 'O') {
            cout << "Player O wins!\n";
            break;
        } else if (winner == 'D') {
           cout << "The game ends in a draw!\n";
            break;
        }

        bot_moves(game_board, player, bot, difficulty);
        display_game_board(game_board);
        cout << "\n\n\n";

        winner = check_winner(game_board);

        if (winner == 'X') {

            std::cout << "Player X wins!\n";
            break;

        } else if (winner == 'O') {

            std::cout << "Player O wins!\n";
            break;

        } else if (winner == 'D') {

            std::cout << "The game ends in a draw!\n";
            break;

        }
    }

  } else {
    int choice_p1 = 0;
    int choice_p2 = 0;

    Player* player1 = nullptr;
    Player* player2 = nullptr;
    bool continue_gmae = true;

    while(continue_gmae){
        char mark_p1;
        string name_p1;

        char mark_p2;
        string name_p2;

        cout << "Player 1 please enter your name: ";
        getline(cin >> ws, name_p1);

        while (name_p1.empty()) {
            cout << "Name cannot be empty. Please enter your name: ";
            getline(cin >> ws, name_p1);
        }

        cout << "Hello " << name_p1 << " please choose your player mark: ";
        cin >> mark_p1;

        while (mark_p1 == ' ' || !isprint(mark_p1) || isdigit(mark_p1)) {
            cout << "Invalid entry! Please choose a valid symbol that isn't a number or space: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> mark_p1;
        }

        while (true) {
            cout << name_p1 << ", choose your class:\n1. Alchemist (Swap 2 marks)\n2. Paladin (Move a mark)\n";
            cin >> choice_p1;

            if (cin.fail() || (choice_p1 != 1 && choice_p1 != 2)) {
                cout << "Invalid choice! Please enter 1 or 2.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> choice_p1;
            }  else {break;}
        }


        if(choice_p1 == 1){
            player1 = new Alchemist (name_p1, mark_p1);
        } else {
            player1 = new Paladin (name_p1, mark_p1);
        }


        cout << "Player 2 please enter your name: ";
       getline(cin >> ws, name_p2);

        while (name_p2.empty()) {
            cout << "Name cannot be empty. Please enter your name: ";
            getline(cin >> ws, name_p2);
        }

        cout << "Hello " << name_p2 << " please choose your player mark: ";
        cin >> mark_p2;

        while (mark_p1 == mark_p2 || mark_p2 == ' ' || !isprint(mark_p2) || isdigit(mark_p2)){
            cout << "Invalid entry! Please choose a valid symbol that isn't a number or empty space: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> mark_p2;

        }

        while (true) {
            cout << name_p2 << ", choose your class:\n1. Alchemist (Swap 2 marks)\n2. Paladin (Move a mark)\n";
            cin >> choice_p2;

            if (cin.fail() || (choice_p2 != 1 && choice_p2 != 2)) {
                cout << "Invalid choice! Please enter 1 or 2.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {break;}
        }


        if(choice_p2 == 1){
            player2 = new Alchemist (name_p2, mark_p2);
        } else {
            player2 = new Paladin (name_p2, mark_p2);
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        
        Player* current_player = player1;

        while(true){
            int ability = 0;

            //Displaying game board
            cout << "\n\n";
            display_game_board(game_board);
            cout << "\n\n";

            cout << current_player -> getName() <<" its your turn to play. (" << current_player->getMark() <<") \n";

            while (true) {
                cout << "Would you like to use your ability(Enter 1) or make a regular move(Enter 2)? ";
                cin >> ability;

                if (cin.fail() || (ability != 1 && ability != 2)) {
                    cout << "Invalid input! Please enter 1 or 2.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else {break;}
            }

            if(ability == 1) {
                current_player->useAbility(game_board);
            } else {
                player_input(current_player->getMark(), game_board);
            }

            //Showing updated game board after a move is made.
            cout << "\n\n";
            display_game_board(game_board);
            cout << "\n\n";

            //Checking for winner after every valid move is made.
            char winner = check_winner(game_board, *player1, *player2);
            if(winner == current_player->getMark()){
                cout << current_player->getName()<< " wins this round!";
                break;

            } else if(winner == 'D'){cout << "This rounds ends in a draw!"; break;}

            //Switching players.
            current_player = (current_player == player1) ? player2 : player1;
        }

        delete player1;
        delete player2;

        char restart;
        while (true) {
            cout << "Would you like to play again? Enter (Y or N): ";
            cin >> restart;

            if (cin.fail() || (toupper(restart) != 'Y' && toupper(restart) != 'N')) {
            cout << "Invalid input! Please enter Y or N.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {break;}
}

        if(restart == 'Y' || restart == 'y'){
            for(int i = 0 ; i < 9; i++){
                game_board[i] = i + '1';
            }
            continue;
        } else {
            cout << "Thanks for playing tictactoe.";
            continue_gmae = false;  
        }
    }

}
        
}
// g++ tictactoe.cpp functions.cpp -o tictactoe.exe
// ./tictactoe.exe