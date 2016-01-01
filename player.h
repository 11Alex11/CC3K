#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "textdisplay.h"
#include "floor.h"
#include "vector.h"
#include <cstdlib>
#include <iostream>
#include "potion.h"
#include "treasure.h"
#include "enemy.h"

#include <string>
#include <vector>
#include "utilities.h"

const std::string HUMAN_NAME = "Human";
const std::string ELF_NAME = "Elf";
const std::string DWARF_NAME = "Dwarf";
const std::string ORC_NAME = "Orc";


class Floor;
class Enemy;

class Player: public Entity
{
protected:
  
  int attack, attackModifier, defence, defenceModifier, health, gold;
private:

  static Player* player;
  std::string actions;

  /*
    Loops through all adjacent cells, and calls observe() on them. Adds
    them to an observed string and returns that string. Mainly used for
    potion detection.
  */
  std::string observeAdjacentCells();

  /*
    Picks up any items the player is standing on. Mostly used for
    treasure. Logs actions accordingly
  */
  virtual void pickUpItems();
  
  /*
    Logs an action to be drawn on the text display footer.
  */
  void logAction(std::string action);

public:
  Player(std::string name, int x, int y,Floor *floor);
  virtual ~Player();
  
  /*
    A singleton/factory method that allows you to initialize a new
    player if the old one is deleted, and gives you an already
    initialized one if it has not been deleted. Has an optional
    parameter for specifying the race of the new player.
  */
  static Player* getPlayer(std::string name="");
  
  /*
    Changes the players floor to the current floor, at the new position,
    and removes all floor - specific stats effects
  */
  virtual void setFloor(int x, int y, Floor* floor);
  
  /*
    Allows the player to be struck by attackers. Calculates the damage
    done to the player and decrements the player's health, and logs
    actions accordingly
  */
  virtual int strike(int attackPower, Entity& striker);
  
  /*
    Called by Game, commands the player to move to a new destination. If
    the player can collide with anything in the target cell, the player
    will not move. Logs actions accordingly.
  */
  virtual void move(int x, int y, std::string direction);
  
  /*
    A place for the player to do it's static turn by turn
    things. Currently just observes adjacent cells, and logs actions
    accordingly.
  */
  virtual Vector tick();
  
  /*
    A method so that Game can command a player to attack a target
    cell. The player will attack all attackable targets in that
    cell. Logs actions accordingly.
  */
  virtual void attackTarget(int destx, int desty);
  
  /*
    Commands the player to use a potion at a target destination. Calls
    use(Player*) on all potions in that destination. Logs actions
    accordingly.
  */
  virtual void usePotion(int destx, int desty);
  
  /*
    Allows an external entity to give a player attack power (the amount
    given can be negative). The player's total attack cannot go below
    zero, and the change in stat is added to a modifier variable, so
    the effects can be reversed later on.
  */
  virtual int giveAttack(int attack);
  
  /*
    Allows an external entity to give a player defence power (the amount
    given can be negative). The player's total defence cannot go below
    zero, and the change in stat is added to a modifier variable, so
    the effects can be reversed later on.
  */
  virtual int giveDefence(int defence);
  
  /*
    Allows an external entity to give health to the player, and prevents
    the players health becoming subzero
  */
  virtual int giveHealth(int health);
  
  virtual int giveGold(int gold);

  /*
    Draws the player at its position on the text display. Also draws
    player stats and actions on the text display Footer.
  */
  void draw(TextDisplay& td);

  
  virtual int getScore() const;
  virtual int getX() const;
  virtual int getY() const;
  virtual bool isAlive() const;

  void gameOver();
};


class Human: public Player
{
public:
  Human();
  
  // Overloads getScore according to special human rules
  int getScore() const;
};

class Elf: public Player
{
private:
  
public:
  Elf();
  /*
    Overloads all potion methods so that elfs can only be positively
    effected by potions, according to special elf rules
  */

  int giveHealth(int health);
  int giveAttack(int attack);
  int giveDefence(int defence);
};

class Orc: public Player
{
private:
public:
  Orc();
  int giveGold(int gold); // overloads givegold so that orcs only get half the gold they pick up
};

class Dwarf: public Player
{
private:
public:
  Dwarf();
  int giveGold(int gold); // overloads givegold so dwarfs get twice the gold 
};

  
#endif
  
