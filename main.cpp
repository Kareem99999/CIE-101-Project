#include "./Core/Game.h"
#include <windows.h>
#pragma comment(lib, "winmm.lib")


int main()
{
	bool existing = true;
	//Plays background music in a loop
	PlaySound("Sound\\background.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (existing) {
		//Create an object of controller
		Game game;

		existing = game.go();
	}
}
