#include "game.h"

Game* Game::game = NULL;


Game::Game()
{
  td = new TextDisplay;
}

Game::~Game()
{
  delete td;
}

void Game::cleanup()
{
  delete Game::game;
}


Game* Game::getGame()
{
  if (Game::game == NULL)
    {
      Game::game = new Game;
      atexit(cleanup);
    }
  return game;
}




/*
  Draws the current floor to the textdisplay, and prints the
  textdisplay. Also draws some of its own information onto the footer.
*/
void Game::draw()
{
  for (int x = 0; x < floors[currentFloor]->getHeight(); x++)
    {
      for (int y = 0; y < floors[currentFloor]->getWidth(); y++)
        {
          floors[currentFloor]->grid[x][y][0]->draw(*td);
        }
    }
  
  std::string floorMessage = "Floor ";
  floorMessage += int_to_string(currentFloor + 1);
  td->writeStringToFooter(floorMessage, floorWidth - (floorMessage.size() + 5), 0);
  
  std::cout << *td;
}


/*
  Simulates the game world for one round by calling tick on each
  entity. Avoids simulating the same entity more than once per tick by
  having an array of bools marking which cells still need simulation
*/
void Game::tick()
{
  bool flags [floorHeight][floorWidth];
  for (int x = 0; x < floorHeight; x++)
    {
      for (int y = 0; y < floorWidth; y++)
        {
          flags[x][y] = false;
        }
    }
  
  for (int x = 0; x < floors[currentFloor]->getHeight(); x++)
    {
      for (int y = 0; y < floors[currentFloor]->getWidth(); y++)
        {
          if (!flags[x][y])
            {
              Vector flag = floors[currentFloor]->grid[x][y][0]->tick();
              flags[flag.getX()][flag.getY()] = true;
                   
            }
        }
    }
}


/*
  Sets the Player so that it is in the correct starting position for a
  new floor
*/

void Game::findAndSetPlayer()
{
  Player* player = Player::getPlayer();
  player->setFloor(floors[currentFloor]->getPlayerX(), floors[currentFloor]->getPlayerY(), floors[currentFloor]);
}


/*
  Starts a new round of the game, handling all command line
  interaction as well as calling the necessary administrative
  functions to simulate/draw the floor.
*/

int Game::startGame(int argc, char *argv[])
{
  bool running = true;
  currentFloor = 0;
  std::string command;


  // Handles race selection
  std::cout << "Select Race [(h)uman|(e)lf|(d)warf|(o)rc]" << std::endl; 
  std::cin >> command;
  Player* player;
  if (command == "o")
    {
      player = Player::getPlayer(ORC_NAME);
    }
  else if (command == "d")
    {
      player = Player::getPlayer(DWARF_NAME);
    }
  else if (command == "e")
    {
      player = Player::getPlayer(ELF_NAME);
    }
  else if (command == "h")
    {
      player = Player::getPlayer(HUMAN_NAME);
    }
  else if (command != "q")
    {
      return startGame(argc, argv);
    }
  


  // Handles instantiation and initialization of all of the floors
  if (command == "q")
    {
      running = false;
    }
  else
    {
      int offset=0;
      for (int i = 0; i < numFloors; i++)
        {
          if (argc == 2)
            {
              floors.push_back(new Floor(argv[1]));
            }
          else{
		
 		floors.push_back(new Floor("random"));
	  }
	
          floors[i]->init(offset);
	  offset+=25;
        }
      findAndSetPlayer();
      player->tick();
      draw();
    }
  
  // Main loop, handles all in game command line interaction, as well
  // as switching the player from floor to floor and ending the game
  while (running)
    {
      std::cin >> command;
      if (command == "q")
        {
          running = false;
        }
      else if (command == "r")
        {
          endGame();
	  return startGame(argc, argv);
        }
        
      else if (command == "a")
        {
          std::cin >> command;
          Vector dir = getDirection(convertDirection(command));
          player->attackTarget(player->getX() + dir.getX(), player->getY() + dir.getY());
        }
      else if (command == "u")
        {
          std::cin >> command;
          Vector dir = getDirection(convertDirection(command));
          player->usePotion(player->getX() + dir.getX(), player->getY() + dir.getY());
        }
      else if (isValidDirection(command))
        {
          Vector dir = getDirection(convertDirection(command));
          player->move(player->getX() + dir.getX(), player->getY() + dir.getY(), convertDirection(command));
        }
      
      
      if (command != "q" && command != "r")
        {
          if (player->getX() == floors[currentFloor]->getStairsX() && player->getY() == floors[currentFloor]->getStairsY())
            {
              
              
              if (currentFloor + 1 < numFloors)
                {
		  floors[currentFloor]->removeEntity(player->getX(), player->getY(), player);
		  currentFloor++;
                  findAndSetPlayer();
		  player->tick();
                  draw();
                }
	      else
		{
		  running = false;
		}
            }
          else 
            {
              tick();
              
              if (!player->isAlive()) running = false;
              
              draw();
              
            }
        }
    }

  endGame();
  return 0;
}

/*
  Deallocates all dynamically allocated memory and observes
  appropriate end game actions - like printing player score etc.. Does
  not neccessarily mean that the Game object is being destroyed, only
  that the current game is over.
*/

void Game::endGame()
{
  Player* player = Player::getPlayer();
  if (player != NULL)
    {
      std::cout << "Game over! " << std::endl;
      if (!player->isAlive() || (currentFloor == (numFloors-1) && (player->getX() == floors[currentFloor]->getStairsX() && player->getY() == floors[currentFloor]->getStairsY())))
        {
          std::cout << "Player score: " << int_to_string(player->getScore()) << std::endl;
        }
      while(floors.size() != 0)
        {
          delete floors.back();
          floors.pop_back();
        }
    }
  
  WoundDefence::resetWoundDefence();
  WoundAttack::resetWoundAttack();
  BoostAttack::resetBoostAttack();
  BoostDefence::resetBoostDefence();
  RestoreHealth::resetRestoreHealth();
  PoisonHealth::resetPoisonHealth();
  Merchant::resetMerchant();
}

/*
  Converts a direction from the command line representation to our
  internal representation
*/
std::string Game::convertDirection(std::string direction)
{
  if (direction == "no") return "North";
  if (direction == "so") return "South";
  if (direction == "ea") return "East";
  if (direction == "we") return "West";
  if (direction == "ne") return "North-East";
  if (direction == "nw") return "North-West";
  if (direction == "se") return "South-East";
  if (direction == "sw") return "South-West";
  return " ";
}


/*
  Returns a direction vector from a properly formatted direction
  string
 */
Vector Game::getDirection(std::string direction)
{
  if (direction == "North")
    {
      return Vector(-1, 0);
    } 
  else if (direction == "South")
    {
      return Vector(1, 0);
    }
  else if (direction == "East")
    {
      return Vector(0, 1);
    }
  else if (direction == "West")
    {
      return Vector(0, -1);
    }
  else if (direction == "North-East")
    {
      return Vector(-1, 1);
    }
  else if (direction == "North-West")
    {
      return Vector(-1, -1);
    }
  else if (direction == "South-East")
    {
      return Vector(1, 1);
    }
  else if (direction == "South-West")
    {
      return Vector(1, -1);
    }
  return Vector(0, 0);
}


bool Game::isValidDirection(std::string input)
{
  Vector direction = getDirection(convertDirection(input));
  return (!(direction.getX() == 0 && direction.getY() == 0));
}
