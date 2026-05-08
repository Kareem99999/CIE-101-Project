#include "./Core/Game.h"


int main()
{
	bool existing = true;
	while (existing) {
		//Create an object of controller
		Game game;

		existing = game.go();
	}
}
