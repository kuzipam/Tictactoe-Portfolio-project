# Tic Tac Toe Portfolio 3 Project

# 1. Changes Made
- Created a Player class that allows players to choose their own marks and enter their names.
- In Portfolio 1, the game loop and functions were hardcoded to only work with X and O. This version removes that restriction.
- Overloaded the check_winner() function to work with the new Player class by referencing player instances.
- Included input validation for all user inputs using fail, clear, and ignore to prevent crashes or invalid states.

Latest changes:
  -Reworked the bot into a class that can be instantiated and reworked its functions to work as class methods.
  -Added the ability to replay matches without restarting the entire program.
  -Updated the check winner function to work with all custom marks instead of only X and O.


# 2. Accomplishments
- The Player class is now the parent class for the two archetypes:  
  - Alchemist(can swap two marks per turn)  
  - Paladin (can move a mark to an adjacent cell)

- Declared useAbility() as a virtual function in the Player class so each subclass can define its own version.
- Implemented swap() in both subclasses for mark manipulation.
-Made an adjacent() helper function used in the Paladin class to check valid adjacent moves.

- The main game loop for regular Tic Tac Toe now allows:
  - Custom player names
  - Custom marks
  - And Dynamic switching between players using a current_player pointer.
  
- For Battle Tic Tac Toe I implemented:
  - Two Player* pointers initialized to nullptr.
  - A Dynamic instantiation of each player’s chosen archetype (`Alchemist` or `Paladin`) at runtime.
  - Included input validation for class selection, marks, names, and move inputs.
  - A restart option at the end of each game round.

- For Bot mode:
  - The entire game mode works with the new bot class and the player class too.
  - Can restart and replay matches with out restarting the program.

- Campaign Tic Tac Toe Mode:
  - Created a campaign mode inspired by many of my favourite games.
  - Has five enemy champions, including a final boss.
  - Has branching paths and different endings depending on the player decisions.
  - Added player stats across battles and events that allow the player to modify their stats.


