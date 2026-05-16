#pragma once
#include <chrono>
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../Core/GameObject.h"
#include "../Entities/food.h"
#include "../UI/BudgetBar.h"
#include "../UI/Toolbar.h"
using TIMER = std::chrono::steady_clock;
using TIME = TIMER::time_point;

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
	int remainingInSeconds() const;
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
	eggs** gameEggslist = new eggs* [100];
	int eggsCounter = 0;
	int totalcreatedeggs = 0;
	milk** gameMilklist = new milk*[100];
	int milkCounter = 0;
	int totalcreatedmilk = 0;
	Wolf* gameWolf;
	background* gameBackground;
	int static level;
public:
	Timer* gameTimer;
	Timer* wolf_delay;
	int budget = 2000;
	int targetBudget = budget + 1000;
	bool ispaused;
	bool gameEnded;
	bool timeToRestart = false;
	static bool shouldLoad;
	Game();
	~Game();

	clicktype getMouseClick(int& x, int& y) const; //Get coordinate where user clicks and returns click type (left/right)
	string getSrting() const;	 //Returns a string entered by the user
	void lvlUp();
	int getTarget();
	window* CreateWind(int, int, int, int) const; //creates the game window
	void createToolbar();
	void createBudgetbar();
	Budgetbar* getBudgetbar() const;
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
	void changeEggcount();
	void changeMilkcount();
	Farm* getFarm() const;
	void decreasemilkcount();
	void decreaseeggscount();
	bool go();
	void saving() const;
	void startLoading();
	void restart();
	void createbackground();
	void render();

	window* getWind() const;		//returns pointer to the graphics window
};

