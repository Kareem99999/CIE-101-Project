#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../UI/BudgetBar.h"
#include "../Core/Timer.h"
#include "../Core/GameObject.h"

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

public:
	int budget = 20000;
	Game();
	~Game();

	clicktype getMouseClick(int& x, int& y) const; //Get coordinate where user clicks and returns click type (left/right)
	string getSrting() const;	 //Returns a string entered by the user


	window* CreateWind(int, int, int, int) const; //creates the game window
	void createToolbar();
	void createBudgetbar();
	void clearBudget() const;
	void createTimer();
	string modifyTimerToStandard() const;
	void printBudget(string msg) const;
	void clearStatusBar() const;	//Clears the status bar

	void printMessage(string msg) const;	//Print a message on Status bar

	void createFarm();
	void redrawFarm() const;
	void createWarehouse();
	void createFoodArea();
	Farm* getFarm() const;

	void go() const;

	window* getWind() const;		//returns a pointer to the graphics window
};

