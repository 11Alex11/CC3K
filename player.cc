#include "player.h" 


Player::Player(std::string name, int x, int y,Floor* floor): Entity( name, x, y,floor)
{
  actions = "";
  gold = 0;
  attackModifier = 0;
  defenceModifier = 0;
  logAction("PC has spawned");
}

Player::~Player() 
{
  Player::player = NULL;
}

Player* Player::player = NULL;

/*
  A singleton/factory method that allows you to initialize a new
  player if the old one is deleted, and gives you an already
  initialized one if it has not been deleted. Has an optional
  parameter for specifying the race of the new player.
*/
Player* Player::getPlayer(std::string name)
{
  if (Player::player == NULL)
    {
      if (name == ELF_NAME)
        {
          Player::player = new Elf;
        }
      else if (name == ORC_NAME)
        {
          Player::player = new Orc;
        }
      else if (name == HUMAN_NAME)
        {
          Player::player = new Human;
        }
      else if (name == DWARF_NAME)
        {
          Player::player = new Dwarf;
        }
    }
  return Player::player;
}

/*
  Changes the players floor to the current floor, at the new position,
  and removes all floor - specific stats effects
*/
void Player::setFloor(int x, int y, Floor* floor)
{
  attack -= attackModifier;
  attackModifier = 0;
  
  defence -= defenceModifier;
  defenceModifier = 0;

  this->x = x;
  this->y = y;
  this->floor = floor;
  floor->insertEntity(x, y, this);
}


/*
  Allows the player to be struck by attackers. Calculates the damage
  done to the player and decrements the player's health, and logs
  actions accordingly
*/
int Player::strike(int attackPower, Entity& striker)
{
  std::string action = "";
  int damage = 0;
  int missChance=rand()%2;
  if(missChance==0)
    {
      action += striker.getName();
      action += " tried to strike PC, but missed";
      logAction(action);
    }
  
  else
    {
      // ceiling integer division: ((a + b - 1) / b)
      damage = ((attackPower*100 + (100 + defence) - 1) / (100 + defence));
      health -= damage;
      action = striker.getName();
      action += " deals ";
      action += int_to_string(damage);
      action += " damage to PC";

      if (health < 0)
        {
	  damage = damage + health;
          health = 0;
        }
      logAction(action);
    }
  return damage;
}


/*
  Called by Game, commands the player to move to a new destination. If
  the player can collide with anything in the target cell, the player
  will not move. Logs actions accordingly.
*/

void Player::move(int destx, int desty, std::string direction)
{
  int numEntities = floor->grid[destx][desty].size();
  bool willNotCollide = true;
  for (int i = 0; i < numEntities; i++)
    {
      if ((floor->grid[destx][desty][i])->canCollideWith(this))
        {
          willNotCollide = false;
        }
    }
  if (willNotCollide)
    {
      floor->moveEntity(x, y, destx, desty, this);
      x = destx;
      y = desty;
      
      std::string action = "PC moves ";
      action += direction;
      logAction(action);
      pickUpItems();
    }
}


/*
  A place for the player to do it's static turn by turn
  things. Currently just observes adjacent cells, and logs actions
  accordingly.
*/
Vector Player::tick()
{
  std::string observation = observeAdjacentCells();
  if (observation != "")
    {
      std::string action = "PC ";
      action += observation;
      logAction(action);
    }

  Vector pos(x, y);
  return pos;
}

/*
  A method so that Game can command a player to attack a target
  cell. The player will attack all attackable targets in that
  cell. Logs actions accordingly.
*/
void Player::attackTarget(int destx, int desty)
{
  int numEntities = floor->grid[destx][desty].size();
  Enemy* enemy = NULL;
  for (int i = 0; i < numEntities; i++)
    {
      enemy = dynamic_cast<Enemy*>(floor->grid[destx][desty][i]);
      if (enemy != NULL)
        {
          std::string enemyName = enemy->getName();
          int initialHealth = enemy->getHealth();
          int finalHealth = enemy->strike(attack);
          std::string action = "PC deals ";
          action += int_to_string(initialHealth - finalHealth);
          action += " damage to ";
          action += enemyName;
          action += "(";
          action += int_to_string(finalHealth);
          action += " HP)";
          logAction(action);
          break;
        }
    }
}

/*
  Loops through all adjacent cells, and calls observe() on them. Adds
  them to an observed string and returns that string. Mainly used for
  potion detection.
*/
std::string Player::observeAdjacentCells()
{
  std::string action = "";
  std::string message = "";
  for (int dx = -1; dx <= 1; dx++)
    {
      for (int dy = -1; dy <= 1; dy++)
        {
          if (!(dx == 0 && dy == 0))
            {
              for (int i = 0; i < floor->grid[x + dx][y + dy].size(); i++)
                {
                  message = floor->grid[x + dx][y + dy][i]->observe();
                  if (message != "")
                    {
                      if (action == "") {action += "sees a ";}
                      else {action += " and sees a ";}
                      action += message;
                      message = "";
                    }
                }
            }
        }
    }
  return action;
}

/*
  Commands the player to use a potion at a target destination. Calls
  use(Player*) on all potions in that destination. Logs actions
  accordingly.
*/
void Player::usePotion(int destx, int desty)
{
  int numEntities = floor->grid[destx][desty].size();
  Potion* potion = NULL;
  for (int i = 0; i < numEntities; i++)
    {
      potion = dynamic_cast<Potion*>(floor->grid[destx][desty][i]);
      if (potion != NULL)
        {
          std::string action = "PC uses ";
          action += potion->getName();
          potion->use(this);
          logAction(action);
          break;
        }
    }
}

/*
  Picks up any items the player is standing on. Mostly used for
  treasure. Logs actions accordingly
*/
void Player::pickUpItems()
{
  Treasure* treasure = NULL;
  for (int i = 0; i < floor->grid[x][y].size(); i++)
    {
      treasure = dynamic_cast<Treasure*>(floor->grid[x][y][i]);
      if (treasure != NULL)
        {
          treasure->use(*this);
	  logAction("PC picked up some treasure");
          break;
        }
    }
}

/*
  Allows an external entity to give a player attack power (the amount
  given can be negative). The player's total attack cannot go below
  zero, and the change in stat is added to a modifier variable, so
  the effects can be reversed later on.
*/
int Player::giveAttack(int attack)
{
  this->attack += attack;
  if (this->attack < 0)
    {
      attack = attack - this->attack;
      this->attack = 0;
    }
  
  attackModifier += attack;
  return attack;
}

/*
  Allows an external entity to give a player defence power (the amount
  given can be negative). The player's total defence cannot go below
  zero, and the change in stat is added to a modifier variable, so
  the effects can be reversed later on.
*/
int Player::giveDefence(int defence)
{
  this->defence = this->defence + defence;
  if (this->defence < 0)
    {
      
      defence = defence - this->defence;
      this->defence = 0;
    }
  defenceModifier += defence;
  return defence;
}

/*
  Allows an external entity to give health to the player, and prevents
  the players health becoming subzero
 */
int Player::giveHealth(int health)
{
  this->health += health;
  if (this->health < 0)
    {
      health = health - this->health;
      this->health = 0;
    }
  return health;
}

int Player::giveGold(int gold)
{
  this->gold += gold;
  return gold;
}


/*
  Draws the player at its position on the text display. Also draws
  player stats and actions on the text display Footer.
*/
void Player::draw(TextDisplay& td)
{
  td.notify(x, y, '@');
  std::string l = "Race: ";
  l += getName();
  l += " Gold: ";
  l += int_to_string(gold);
  td.addFooterLine(l);
  
  l = "HP: ";
  l += int_to_string(health);
  td.addFooterLine(l);
  
  l = "Atk: ";
  l+= int_to_string(attack);
  td.addFooterLine(l);

  l = "Def: ";
  l += int_to_string(defence);
  td.addFooterLine(l);
  

  
  l = "Action: ";
  l += actions;
  actions = "";
  td.addFooterLine(l);
}

/*
  Logs an action to be drawn on the text display footer.
*/
void Player::logAction(std::string action)
{
  actions += action;
  actions += ". ";
}

int Player::getX() const
{
  return x;
}

int Player::getY() const
{
  return y;
}

bool Player::isAlive() const
{
#ifdef IMMORTAL
  return true;
#endif
  
  return health > 0;
}

int Player::getScore() const
{
  return gold;
}

Human::Human(): Player(HUMAN_NAME, 0, 0, NULL)
{
  health = 140;
  attack = 20;
  defence = 20;
}

// Overloads getScore according to special human rules
int Human::getScore() const
{
  return gold + gold/2;
}

Elf::Elf(): Player(ELF_NAME, 0, 0, NULL)
{
  health = 140;
  attack = 30;
  defence = 10;
}

/*
  Overloads all potion methods so that elfs can only be positively
  effected by potions, according to special elf rules
 */

int Elf::giveHealth(int health)
{
  if (health < 0)
    {
      health = -1*health;
    }
  this->health += health;
  return health;
}

int Elf::giveAttack(int attack)
{
  if (attack < 0)
    {
      attack = -1*attack;
    }
  this->attackModifier += attack;
  this->attack += attack;
  return health;
}

int Elf::giveDefence(int defence)
{
  if (defence < 0)
    {
      defence = -1*defence;
    }
  this->defenceModifier += defence;
  this->defence += defence;
  return health;
}

Orc::Orc(): Player(ORC_NAME, 0, 0, NULL)
{
  health = 180;
  attack = 30;
  defence = 25;
}

// overloads givegold so that orcs only get half the gold they pick up
int Orc::giveGold(int gold)
{
  gold = gold/2;
  this->gold += gold;
  return gold;
}


Dwarf::Dwarf(): Player(DWARF_NAME, 0, 0, NULL)
{
  health = 100;
  attack = 20;
  defence = 30;
}

// overloads givegold so dwarfs get twice the gold 
int Dwarf::giveGold(int gold)
{
  gold = 2*gold;
  this->gold += gold;
  return gold;
}

