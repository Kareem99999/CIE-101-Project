#pragma once
#include "../CMUgraphicsLib/CMUgraphics.h"
#include "../UI/Toolbar.h"
#include "../UI/BudgetBar.h"
#include "../Entities/food.h"
#include <chrono>
#include "../Core/GameObject.h"
#include <random>
using TIMER = std::chrono::steady_clock;
using TIME = TIMER::time_point;
enum weathertype {
	sunny,
	deserted,
	rainy
};
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
	eggs** gameEggslist;
	int eggsCounter = 0;
	int totalcreatedeggs = 0;
	milk** gameMilklist;
	int milkCounter = 0;
	int totalcreatedmilk = 0;
	Wolf** gameWolves;
	int static level;
	background* gameBackground;
	int totalcreatedwolves = 0;
	int currentWolves = 0;
	weathertype currentweather;
	Timer* weathertimer;
	Timer* weatherMessageTimer;
	bool showWeatherMessage = false;

public:
	Timer* gameTimer;
	Timer* wolf_delay;
	int budget = 2000;
	int static WolfNextTimeStamp;
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
	//void redrawFarm() const;
	void createWarehouse();
	int getEggcount();
	int getMilkcount();
	void changeEggcount();
	void changeMilkcount();
	void createEgg(Chick* chick);
	void createMilk(Cow* cow);
	Farm* getFarm() const;
	void decreasemilkcount();
	void decreaseeggscount();
	bool go();
	void saving() const;
	void startLoading();
	void restart();
	void createbackground();
	void render();
	weathertype getCurrentWeather() const;
	void changeweather();
	void applyWeather(weathertype);
	window* getWind() const;		//returns pointer to the graphics window
};

