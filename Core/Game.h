#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../UI/BudgetBar.h"
#include "../Entities/food.h"
#include <chrono>
#include "../Core/GameObject.h"

using TIMER = std::chrono::steady_clock;
using TIME = TIMER::time_point;

static int lvl = 1;	// Global variable to keep track of the current level of the game

class Timer {
private:
	TIME start = TIME();
	TIME end = TIME();
	TIME pauseStart;
	std::chrono::milliseconds pausedTime = std::chrono::milliseconds(0);
	static TIME delay;
public:
	bool isPaused = false;
	Timer(int duration);
	void setDuration(int Duration);
	bool check() const;
	//bool delayed(int duration) const;
	long long elapsed() const;
	long long remaining() const;
	void paused();
	void resume();
};

class Game
{
private:
	window* pWind;	//Pointer to the CMU graphics window
	Toolbar* gameToolbar;
	Budgetbar* gameBudgetbar;
	Farm* gameFarm;
	Warehouse* gameWarehouse;
	eggs** gameEggslist = new eggs* [15];
	int eggsCounter = 0;
	int totalcreatedeggs = 0;
	milk** gameMilklist = new milk*[15];
	int milkCounter = 0;
	int totalcreatedmilk = 0;
	Wolf* gameWolf;
	// Level variable is global

public:
	// Level ^^^^^^^^^^
	void lvlUp(Game* pGame);   // Level control function
	int getlvl() const;        // Reurns the current level of the game

	Timer* gameTimer;
	Timer* wolf_delay;
	// Timer shi ^^^^^
	int budget = 2000;
	bool ispaused;
	bool gameEnded;
	bool timeToRestart = false;
	static bool shouldLoad;
	Game();
	~Game();

	clicktype getMouseClick(int& x, int& y) const; //Get coordinate where user clicks and returns click type (left/right)
	string getSrting() const;	 //Returns a string entered by the user


	window* CreateWind(int, int, int, int) const; //creates the game window
	void createToolbar();
	void createBudgetbar();
	void clearBudget() const;
	void createTimer();
	void createWolf();
	string modifyTimerToStandard() const;
	void printBudget(string msg) const;
	void clearStatusBar() const;	//Clears the status bar

	void printMessage(string msg) const;	//Print a message on Status bar

	void createFarm();
	void redrawFarm() const;
	void createWarehouse();
	int getEggcount();
	int getMilkcount();
	Farm* getFarm() const;
	void decreasemilkcount();
	void decreaseeggscount();
	bool go();
	void saving() const;
	void startLoading();
	void restart();

	window* getWind() const;		//returns pointer to the graphics window
};

