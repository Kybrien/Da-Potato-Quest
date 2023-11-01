#include <iostream>

#include "Game.h"

int main()
{
	Game DPQ;
	DPQ.Init();
	std::cout << "Game Initialised" << std::endl;
	DPQ.Run();

	return 0;
}
