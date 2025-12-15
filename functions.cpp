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

//Overloading function to work with the new player class and marks.
char check_winner(char game_board[9], char p1mark, char p2mark) {

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

        if(game_board[i] != p1mark && game_board[i] != p2mark){
            full = false;
            break; 
        }
    }
    if (full) return 'D';

    //This returns empty so the much can continue if there isnt a winner yet.
    return ' '; 
}

//This function uses the moves from the Wikipedia link to find the most optimal move on the board that the bot can use.
int Bot::find_optimal_move(char game_board[9], char player, char bot) {

    //Using a loop for the bot to go through all the empty spaces to look for a winning move.  
    for (int i = 0; i < 9; i++) {

        if (game_board[i] != player && game_board[i] != bot) {

            char backup = game_board[i];
            game_board[i] = bot;

            if (check_winner(game_board, player, bot) == bot) {
                game_board[i] = backup;
                return i;
            }
            game_board[i] = backup;
        }
    }

    //This does the same as the previous loop but the bot looks for an empty space that will block the player from winning.
    for (int i = 0; i < 9; i++) {

        if (game_board[i] != player && game_board[i] != bot) {

            char backup = game_board[i];
            game_board[i] = player;
            
            if (check_winner(game_board, player, bot) == player) {
                game_board[i] = backup;
                return i;
            }
            game_board[i] = backup;
        }
    }

    //The bot takes the centre if its free.
    if (game_board[4] != player && game_board[4] != bot) return 4;

    //The bots takes the opposite corner from the player if its free.
    if (game_board[0] == player && game_board[8] == player) return 8;
    if (game_board[8] == player && game_board[0] == player) return 0;
    if (game_board[2] == player && game_board[6] == player) return 6;
    if (game_board[6] == player && game_board[2] == player) return 2;

    //The bots takes any corner if its free.
    int corners[4] = {0, 2, 6, 8};

    for (int i = 0; i < 4; i++) {if (game_board[corners[i]] != player && game_board[corners[i]] != bot) return corners[i];}

    //The bot takes any side spot if its free too.
    int sides[4] = {1, 3, 5, 7};

    for (int i = 0; i < 4; i++) {if (game_board[sides[i]] != player && game_board[sides[i]] != bot) return sides[i];}

    //The bots doesnt have any moves to make.
    return -1; 
}

//Picks a random move that is NOT the optimal one
int Bot::random_move(char game_board[9], int optimal, char player, char bot) {

    std::vector<int> bot_choices;

    for (int i = 0; i < 9; i++) {

        if (game_board[i] != player && game_board[i] != bot && i != optimal) {
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
void Bot::bot_moves(char game_board[9], char player, char bot, int diff_choice) {

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
        case 5: errorChance = 100; break;//Added this only for the campaign so that the bot make its moves randomly. This forces a 100 percent error chance so that the bot always uses the random move function.
    }

    //Using rand to sort of roll a dice to decide if the bot should make an error or not.
    int random_dice = rand() % 100;

    if (random_dice < errorChance) {

        //Random move function is called if the the bot does make an error.
        move = random_move(game_board, optimal, player, bot);
    }

    //The bot makes its move. Since the bot returns -1 in the optimal move function if it doesnt find a move, I used it as a condition to avoid any errors.
    if (move != -1 && game_board[move] != player && game_board[move] != bot) {
        game_board[move] = bot;
    }
}

Player::Player(string n, char m, int hp, int def, int atk)
    : name(n), mark(m), health(hp), defense(def), attack(atk) {}

string Player::getName() const {return name;}

char Player::getMark() const {return mark;}
string Player::getplayerclass(){return "Player";}

void Player::useAbility(char game_board[9]){}

int Player::getHealth() const {return health;}

int Player::getAttack() const {return attack;}

int Player::getDefense() const {return defense;}

void Player::takeDamage(int amount) {
    health -= amount;
    if (health < 0) {health = 0;}
}

void Player::heal(int amount) {health += amount;}

void Player::modifyAttack(int delta) {
    attack += delta;
    if (attack < 1) {attack = 1;}
}

void Player::modifyDefense(int delta) {
    defense += delta;
    if (defense < 0) {defense = 0;}
}


//Turned my original bot into a class to create instances that are used in the campaign mode.
Bot::Bot(const string& n, int hp, int atk, int def, char m)
    : name(n), health(hp), defense(def), attack(atk), mark(m) {}
    
void Bot::useAbility(char game_board[9]){}


Alchemist:: Alchemist(string n, char m, int hp, int def, int atk) : Player(n, m, hp, def, atk){};
string Alchemist::getplayerclass(){return "Alchemist";}

void Alchemist::useAbility(char game_board[9]) {
    int marks = 0;

    //Count all of the player's marks on the board.
    for (int i = 0; i < 9; i++) {if (!isdigit(game_board[i])){marks++;}}

    //Checks for at least two marks
    if (marks < 2) {
        std::cout << name << ", there must to be at least 2 marks on the game board to use your special ability.\n";
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

    while (spot1 < 1 || spot1 > 9 || spot2 < 1 || spot2 > 9 || spot1 == spot2) {
        std::cout << "Invalid input! Please try entering two different numbers (1-9): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> spot1 >> spot2;
    }

    //Had to rework this abiltiy as well to not swap digits and stop swaps with the same marks.
    int a = spot1 - 1;
    int b = spot2 - 1;

    if (isdigit(game_board[a]) || isdigit(game_board[b])) {
        std::cout << "Invalid swap: you can only swap occupied marks (not empty spaces).\n";
        return;
    }

    if (game_board[a] == (game_board[b])) {
        std::cout << "These spots have the same marks. Nothing swapped.\n";
        return;
    }

    std::swap(game_board[a], game_board[b]);
    std::cout << "Swap complete!\n";
}


Paladin::Paladin(string n, char m, int hp, int def, int atk) : Player(n, m, hp, def, atk){};
string Paladin::getplayerclass(){return "Paladin";}


bool adjacent(int spot1, int spot2) {
    
    int row_spot1 = (spot1 - 1) / 3;
    int col_spot1 = (spot1 - 1) % 3;
    int row_spot2   = (spot2 - 1) / 3;
    int col_spot2   = (spot2- 1) % 3;

    return (abs(row_spot1 - row_spot2) == 1 && col_spot1 == col_spot2) || (abs(col_spot1 - col_spot2) == 1 && row_spot1 == row_spot2);

}

void Paladin::useAbility(char game_board[9]) {
    bool hasMark = false;

    //Check if the player has at least one mark
    for (int i = 0; i < 9; i++) {if (!isdigit(game_board[i])) {hasMark = true; break;}}

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

    while (cin.fail()|| spot1 < 1 || spot1 > 9|| isdigit(game_board[spot1 - 1]) ) {
        cout << "Invalid input! Pick a square that has a mark (not an empty number 1-9): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> spot1;
    }


    std::cout << "Move to: ";
    std::cin >> spot2;

   while (cin.fail()|| spot2 < 1 || spot2 > 9|| !adjacent(spot1, spot2)|| !isdigit(game_board[spot2 - 1]) ) {
        cout << "Invalid input! Choose an adjacent EMPTY square (1-9): ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> spot2;
    }

    //Updated the ability logic so now the paladin only moves into empyt spaces and the board numbers dont move.
    int from = spot1 - 1;
    int to   = spot2 - 1;

    game_board[to] = game_board[from];
    game_board[from] = (from + 1) + '0'; 

}


// Helper to calculate damage done after a round.
int calcDamage(int atk, int def) {
    int dmg = atk - def;
    if (dmg < 1) dmg = 1;
    return dmg;
}

//Plays a single round of tictactoe.
char play_round(Player &player, Bot &enemy) {
    char game_board[9] = {'1','2','3','4','5','6','7','8','9'};

    char playerMark = player.getMark();
    char enemyMark  = enemy.mark;

    bool playerTurn = true; 

    while (true) {
        display_game_board(game_board);

        if (playerTurn) {
            cout << "\n" << player.getName() << "'s turn (" << playerMark << ").\n";
            player_input(playerMark, game_board);
        } else {
            cout << "\n" << enemy.name << " is making a move (" << enemyMark << ")...\n";
        
            //Bot is set to make random moves always.
            int diff_choice = 5;
            enemy.bot_moves(game_board, playerMark, enemyMark, diff_choice);
        }

        char winner = check_winner(game_board, playerMark, enemyMark);

        if (winner == playerMark) {
            display_game_board(game_board);
            cout << "\n" << player.getName() << " wins this round of tic-tac-toe!\n";
            return 'P';

        } else if (winner == enemyMark) {
            display_game_board(game_board);
            cout << "\n" << enemy.name << " wins this round of tic-tac-toe!\n";
            return 'E';

        } else if (winner == 'D') {
            display_game_board(game_board);
            cout << "\nThis round ends in a draw.\n";
            return 'D';
        }

        playerTurn = !playerTurn;
    }
}

//Battle functions that plays multiple rounds until either the player or enemy wins.
void battle(Player &player, Bot &enemy) {
    cout << "\n====================================\n";
    cout << "Battle vs " << enemy.name << " begins!\n";

    while (player.getHealth() > 0 && enemy.health > 0) {
        cout << "\n------------------------------------\n";
        cout << player.getName() << "  HP: " << player.getHealth()
             << "  ATK: " << player.getAttack()
             << "  DEF: " << player.getDefense() << "\n";

        cout << enemy.name << "     HP: " << enemy.health
             << "  ATK: " << enemy.attack
             << "  DEF: " << enemy.defense << "\n";

        // Play one tic-tac-toe match
        char result = play_round(player, enemy);

        if (result == 'P') {
            int dmg = max(0, player.getAttack() - enemy.defense);
            enemy.health -= dmg;
            cout << "\nYou hit " << enemy.name << " for " << dmg << " damage!\n";
        }
        else if (result == 'E') {
            int dmg = max(0, enemy.attack - player.getDefense());
            player.takeDamage(dmg);
            cout << "\n" << enemy.name << " hits you for " << dmg << " damage!\n";
        }
        else {
            cout << "\nNo dAmage this round.\n";
        }

        if (enemy.health <= 0) {
            cout << "\nYou defeated " << enemy.name << "!\n";
            break;
        }

        if (player.getHealth() <= 0) {
            cout << "\nYou were defeated by " << enemy.name << "...\n";
            break;
        }
    }
}

void moralChoices(const string& enemyName, int &spared, int &executed) {
    cout << "\n" << enemyName << " kneels before you, defeated.\n";
    cout << "What do you do?\n";
    cout << "1. Spare them\n";
    cout << "2. Execute them\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    while (cin.fail() || (choice != 1 && choice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please choose 1 or 2: ";
        cin >> choice;
    }

    if (choice == 1) {
        spared++;
        cout << "\nYou choose mercy.\n";
    } else {
        executed++;
        cout << "\nYou show no mercy.\n";
    }
}

void goodEnding(Player &player) {
    cout << "\nYou spared those who wronged you, those that took everything and everyone from you.\n";
    cout << "They stop doing bad and try to repay the people they hurt.\n";
    cout << "Peace returns through mercy. You finally avenged your family through kindness.\n";
    cout << "\n =====GOOD ENDING=====\n";
}

void badEnding(Player &player) {
    cout << "\nEvery champion lies dead.\n";
    cout << "The name "<< player.getName() <<" inflicts fear into all.\n";
    cout << "You became what you swore to destroy.\n";
    cout << "\n =====BAD ENDING===== \n";
}

void neutralEnding(Player &player) {
    cout << "\nSome were spared. Others werent so lucky.\n";
    cout << "The world heals, but some scars remain.\n";
    cout << "\n =====NEUTRAL ENDING===== \n";
}

void campaign(Player* p){
    Player &player = *p;
    int spared = 0;
    int executed = 0;
    int gold = 0;



    //Intro story
    cout << player.getName() << ", you were born in a peaceful village, living with your family.\n";
    cout << "You lived in harmony with all the other villagers until that peace\n";
    cout << "was shattered the day the Five champions arrived.\n\n";

    cout << "They slaughtered everyone in your village mercilessly.\n";
    cout << "Your family was cut down before your eyes and you were left for dead\n";
    cout << "in your blazing family house.\n";
    cout << "However, through sheer will power you survived.\n\n";

    cout << "Alone and with no one to go to, you left the barren town you called home,\n";
    cout << "trying to recover from that traumatic event.\n";
    cout << "You spent years training, honing your skills and yourself into an unstoppable "
         << player.getplayerclass()  << ".\n";
    cout << "You are now prepared to return back to your homeland and avenge your family\n";
    cout << "by hunting the Five champions that took everything from you.\n\n";

    cout << "Press Enter to begin your journey...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();

    //Enemy bot setup.
    char enemyMark = (player.getMark() == 'X') ? 'O' : 'X';

    Bot champ1("Maliketh", 10, 3, 2, enemyMark);
    Bot champ2("Crucible Knight", 13, 4, 2, enemyMark);
    Bot champ3("Kratos the God of War", 16, 5, 3, enemyMark);
    Bot champ4("Hollow Knight", 18, 6, 3, enemyMark);
    Bot finalBoss("Godfrey the first Elden Lord", 20, 6, 4, enemyMark);

    //First Battle.
    cout << "\nYour journey begins...\n";
    battle(player, champ1);
    if (player.getHealth() <= 0) {
        cout << "\nYou fall to Maliketh.\nYour story ends here.\n";
        return;
    }

    moralChoices(champ1.name, spared, executed);

    //Rewards player with 5 to 10 gold after defeating an enemy
    int reward = 5 + rand() % 6; 
    gold += reward;
    cout << "\nYou found " << reward << " gold. Current gold: " << gold << "\n\n";

    //Event 1 - resting. 
    cout << "\nAfter defeating the Maliketh, you find a small abandoned camp.\n";
    cout << "You rest and recover some strength.\n";
    player.heal(3);
    cout << "You recovered 3 HP. Current HP: " << player.getHealth() << "\n\n";

    //Second Battle.
    battle(player, champ2);
    if (player.getHealth() <= 0) {
        cout << "\nThe Crucible Knight overwhelms you.\n";
        return;
    }
    moralChoices(champ2.name, spared, executed);
    reward = 5 + rand() % 6; 
    gold += reward;
    cout << "\nYou found " << reward << " gold. Current gold: " << gold << "\n\n";


    //Event 2- Merchant.
    cout << "\nA traveling merchant appears.\n";
    cout << "Gold: " << gold << "\n";
    cout << "1) Potion (+3 HP) - 6 gold\n";
    cout << "2) Sharpen Blade (+3 ATK) - 8 gold\n";
    cout << "3) Reinforce Armor (+1 DEF) - 8 gold\n";
    cout << "4) Leave shop\n";

    int shopChoice = 0;
    while (true) {
        cout << "Choose 1-4: ";
        cin >> shopChoice;

        if (cin.fail() || shopChoice < 1 || shopChoice > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid.\n";
        } else break;
    }

    if (shopChoice == 1) {
        if (gold >= 6) {
            gold -= 6;
            player.heal(3);
            cout << "You drink a potion (+3 HP). Gold: " << gold
                 << " | HP: " << player.getHealth() << "\n\n";

        } else {cout << "Not enough gold.\n\n";}

    }else if (shopChoice == 2) {
        if (gold >= 8) {
            gold -= 8;
            player.modifyAttack(3);
            cout << "Your weapon is sharpened (+3 ATK). Gold: " << gold
                 << " | ATK: " << player.getAttack() << "\n\n";

        } else {cout << "Not enough gold.\n\n";}

    } else if (shopChoice == 3) {
        if (gold >= 8) {
            gold -= 8;
            player.modifyDefense(1);
            cout << "Your armor is reinforced (+1 DEF). Gold: " << gold
                 << " | DEF: " << player.getDefense() << "\n\n";

        } else {cout << "Not enough gold.\n\n";}

    } else {cout << "You leave the shop.\n\n";}

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    //Third Battle.
    battle(player, champ3);
    if (player.getHealth() <= 0) {
        cout << "\nKratos the God of War claims your soul.\n";
        return;
    }
    moralChoices(champ3.name, spared, executed);
    reward = 5 + rand() % 6;
    gold += reward;
    cout << "\nYou found " << reward << " gold. Current gold: " << gold << "\n\n";


    //Event 3: Buff.
    cout << "\nYou discover an ancient magical stone statue.\n";
    cout << "A protective aura surrounds you.\n";
    player.modifyDefense(1);
    cout << "DEF increased by 1! Current DEF: " << player.getDefense() << "\n\n";

   
    //Fourth Battle
    battle(player, champ4);
    if (player.getHealth() <= 0) {
        cout << "\nThe Hollow Knight's curse consumes you.\n";
        return;
    }
    moralChoices(champ4.name, spared, executed);
    reward = 5 + rand() % 6;
    gold += reward;
    cout << "\nYou found " << reward << " gold. Current gold: " << gold << "\n\n";


    //Final fight. Boss uses his ability.
    cout << "\nAs you approach the throne room, a chilling roar shakes the ruins.\n";
    cout << "Godfrey the first Elden Lord senses your presence and his fury grows.\n";
    int roll = rand() % 3;

    if (roll == 0) {finalBoss.attack += 3; cout << "Godfrey roars! +3 ATK!\n\n";} 
    else if (roll == 1) {finalBoss.defense += 2;cout << "Godfrey hardens his stance! +2 DEF!\n\n";}
    else {player.modifyDefense(-1);cout << "Godfrey shatters your guard! -1 DEF!\n\n";}


    battle(player, finalBoss);
    if (player.getHealth() <= 0) {
        cout << "\nYou gave everything, but Godfrey the first Elden Lord stands victorious.\n";
        cout << "Your family's memory fades into dust...\n";
        return;
    }

    cout << "\nWith a final strike, you slay Godfrey the first Elden Lord.\n";
    cout << "The Five Champions who destroyed your village are no more.\n";
    cout << "Your family's spirits can finally rest in peace.\n";
    cout << "You, " << player.getName() << " the " << player.getplayerclass()
        << ", have avenged your family.\n\n";

    if (spared >= 3){goodEnding(player);} 
    else if (executed >= 3) {badEnding(player);} 
    else {neutralEnding(player);}
    
}
