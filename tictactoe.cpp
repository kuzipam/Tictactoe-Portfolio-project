#include<iostream>
#include<vector>
#include "iamheaderfile.hpp"
#include <cstdlib>
#include <ctime>


int main() {
    srand(time(0));
    int choice = 0;

    //Creating the game board.
    char game_board[9] = {'1','2','3','4','5','6','7','8','9'};
    while (choice != 1 && choice != 2) {

        std::cout << "Would you like to play against another player or a bot?\n"
                  << "Enter 1 to play against another player or Enter 2 to play against a bot.\n";

        std::cin >> choice;

        if (!std::cin) {

            std::cout << "Invalid input! Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n'); 
            choice = 0; 

        } else if (choice != 1 && choice != 2) {
        std::cout << "Invalid choice! Please enter 1 or 2.\n";

        }
    }

    //If the player chooses option 1, they play against someone else.
    if (choice == 1){

        // Displaying the gameboard.
        display_game_board(game_board);
        
        //Starting the game with a while loop. X is player 1.

        char player = 'X';

        while (true) {
        // Player input
        player_input(player, game_board);

        // Show updated board
        display_game_board(game_board);

        // Check for winner or draw
        char winner = check_winner(game_board);
        if (winner == 'X') {
            std::cout << "Player X wins!\n";
            break;

        } else if (winner == 'O') {
            std::cout << "Player O wins!\n";
            break;

        } else if (winner == 'D'){
            std::cout << "The game ends in a draw!\n";
            break;
        }

        // Switch players
        player = (player == 'X') ? 'O' : 'X';
        std::cout << "Player '" << player << "' please make your move.\n";
    }
    return 0;

    //If not they play against a bot.
    } else {
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
        std::cout << "\n\n\n";

        char winner = check_winner(game_board);
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

        bot_moves(game_board, player, bot, difficulty);
        display_game_board(game_board);
        std::cout << "\n\n\n";

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
  }
}
// g++ tictactoe.cpp functions.cpp -o tictactoe.exe
// ./tictactoe.exe