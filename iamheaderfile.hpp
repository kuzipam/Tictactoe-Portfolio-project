#include<iostream>
#include<vector>

void display_game_board(char game_board[9]);
void player_input(char player, char game_board[9]);
bool check_winner(char game_board[9]);
int find_optimal_move(char game_board[9], char player, char bot);
int random_move(char game_board[9], int optimal);
void bot_moves(char game_board[9], char player, char bot, int diff_choice);
