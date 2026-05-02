#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../UI/BudgetBar.h"
#include <chrono>
#include "../Core/GameObject.h"

using TIMER = std::chrono::steady_clock;
using TIME = TIMER::time_point;

class Timer {
private:
	TIME start = TIME();
	TIME end = TIME();
	static TIME delay;
public:
	Timer(int duration);
	void setDuration(int Duration);
	bool check() const;
	//bool delayed(int duration) const;
	long long elapsed() const;
	long long remaining() const;
};

class Game
{
private:
	window* pWind;	//Pointer to the CMU graphics window
	Toolbar* gameToolbar;
	Budgetbar* gameBudgetbar;
	Farm* gameFarm;
	Warehouse* gameWarehouse;
	FoodArea* gameFoodArea;
	Timer* gameTimer;
	Wolf* gameWolf;

public:
	int budget = 20000;
	bool timeToRestart = false;
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
	void createFoodArea();
	Farm* getFarm() const;
	FoodArea* getFoodArea() const;

	bool go();
	void saving() const;
	void loading();
	void restart();

	window* getWind() const;		//returns a pointer to the graphics window
};

