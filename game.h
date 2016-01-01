#ifndef __GAME_H__
#define __GAME_H__

#include <string>
#include <cstring>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "floor.h"
#include "player.h"
#include "restorehealth.h"
#include "poisonhealth.h"
#include "boostattack.h"
#include "boostdefence.h"
#include "woundattack.h"
#include "wounddefence.h"
#include "merchant.h"
#include "vector.h"
#include "textdisplay.h"
#include "utilities.h"

const int numFloors = 8; // temporary, switch to 8 later 
const int floorWidth = 79;
const int floorHeight = 25;

// Handles starting the game, keeping score, managing floors and
// players
// Should be made into singleton
class Game
{
private:
  TextDisplay* td; 
  std::vector<Floor*> floors; // vector containing all the floors
  unsigned int currentFloor; // the index to the current floor in the floor vector
    
  Game();
  static Game* game; // singleton pointer to game 
  static void cleanup();
  
  /*
    Deallocates all dynamically allocated memory and observes
    appropriate end game actions - like printing player score etc.. Does
    not neccessarily mean that the Game object is being destroyed, only
    that the current game is over.
  */
  void endGame();
  
  /*
    Draws the current floor to the textdisplay, and prints the
    textdisplay. Also draws some of its own information onto the footer.
  */
  void draw();
  
  /*
    Simulates the game world for one round by calling tick on each
    entity. Avoids simulating the same entity more than once per tick by
    having an array of bools marking which cells still need simulation
  */
  void tick();
  
  /*
    Sets the Player so that it is in the correct starting position for a
    new floor
  */
  void findAndSetPlayer();
  
  Vector getDirection(std::string direction); // our internal string representation of a direction into a direction vector
  std::string convertDirection(std::string direction); // converts a direction from input format to our internal representation of direction
  bool isValidDirection(std::string input); // determines if a string is a valid direction in command line format
public:
  ~Game();
 
  static Game* getGame(); // returns a new game, according to the singleton pattern

  /*
    Starts a new round of the game, handling all command line
    interaction as well as calling the necessary administrative
    functions to simulate/draw the floor.
  */
  int startGame(int argc, char *argv[]);
  
};

#endif

// Emacs configuration

// Local Variables:
// mode: c++
// End:
