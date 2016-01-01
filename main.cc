#include "game.h"
#include "time.h"
#include <cstdlib>

#ifdef AUTOMATED_TEST_INPUT
#include <iostream>
#include <fstream>
#endif



int main(int argc, char *argv[])
{
        #ifdef AUTOMATED_TEST_INPUT
        std::ifstream in("fuzz.txt");
        std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
        std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
        #endif

	//generate random generation seed
	srand(time(NULL));
	//creates an instance of the game and starts the game
	Game* game = Game::getGame();
	game->startGame(argc, argv);
	return 0;
}
