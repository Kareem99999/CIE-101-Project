#pragma comment(lib, "winmm.lib")
#include <windows.h>
#include "./Core/Game.h"

int main()
{
	bool existing = true;
	//Plays background music in a loop
	PlaySound("Sound\\ga.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (existing) {
		//Create an object of controller
		Game game;

		existing = game.go();
	}
}
