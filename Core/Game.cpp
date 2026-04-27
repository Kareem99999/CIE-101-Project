#include "Game.h"
#include "../Config/GameConfig.h"
#include "GameObject.h"
#include "../UI/BudgetBar.h"
#include <thread>
#include <chrono>

Game::Game()
{


	//1 - Create the main window
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);

	//2 - create and draw the toolbar
	createToolbar();
	createBudgetbar();
	//3 - create and draw the backgroundPlayingArea
	createWarehouse();
	createFarm();
	createFoodArea();
	//4- Create the Plane
	//TODO: Add code to create and draw the Plane

	//5- Create the Bullet
	//TODO: Add code to create and draw the Bullet

	//6- Create the enemies
	//TODO: Add code to create and draw enemies in random places

	//7- Create and clear the status bar
	clearStatusBar();
	createTimer();
	gameWolf = nullptr;
}


// Timer implementations (moved here so Timer is merged with Game files)
TIME Timer::delay = TIMER::now();
Timer::Timer(int duration) {
	start = TIMER::now();
	end = start + std::chrono::milliseconds(duration);
}

void Timer::setDuration(int Duration) {
	start = TIMER::now();
	end = start + std::chrono::milliseconds(Duration);
}

bool Timer::check() const {
	return (TIMER::now() >= end);
}

long long Timer::elapsed() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(TIMER::now() - start).count();
}

long long Timer::remaining() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - TIMER::now()).count();
}

Game::~Game()
{
}

clicktype Game::getMouseClick(int& x, int& y) const
{
	return pWind->GetMouseClick(x, y);	//Wait for mouse click

}



string Game::getSrting() const
{
	string Label;
	char Key;
	keytype ktype;
	pWind->FlushKeyQueue();
	while (1)
	{
		ktype = pWind->WaitKeyPress(Key);
		if (ktype == ESCAPE)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8)	//BackSpace is pressed
			if (Label.size() > 0)
				Label.resize(Label.size() - 1);
			else
				Key = '\0';
		else
			Label += Key;
		printMessage(Label);
	}
}

window* Game::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(config.bkGrndColor);
	pW->SetPen(config.bkGrndColor, 1);
	pW->DrawRectangle(0, 0, w, h);
	return pW;
}

void Game::createToolbar() 
{
	point toolbarUpperleft;
	toolbarUpperleft.x = 0;
	toolbarUpperleft.y = 0;

	gameToolbar = new Toolbar(this, toolbarUpperleft, 0, config.toolBarHeight);
	gameToolbar->draw();
}

void Game::createFarm()
{
	point FarmRef;
	FarmRef.x = config.windWidth / 4;
	FarmRef.y = config.windHeight * 1 / 3;
	int Height = config.windHeight * 2 / 3.5;
	int Width = config.windWidth / 2;
	BudgetbarIcon::setRangeMinX(FarmRef.x + Farm::getMargin());
	BudgetbarIcon::setRangeMaxX(FarmRef.x + Width - Farm::getMargin());
	BudgetbarIcon::setRangeMinY(FarmRef.y + Farm::getMargin());
	BudgetbarIcon::setRangeMaxY(FarmRef.y + Height - Farm::getMargin());
	gameFarm = new Farm(this, FarmRef, Width, Height, BROWN, DARKGREEN);
	gameFarm->draw();
}

void Game::redrawFarm() const
{
	gameFarm->draw();
	gameFoodArea->draw();
	gameWarehouse->draw();
}

void Game::createWolf()
{
	point p;
	std::random_device rd1;
	std::mt19937 gen1(rd1());
	std::uniform_int_distribution<int> dist1(BudgetbarIcon::getRangeMinX(), (BudgetbarIcon::getRangeMaxX() - Wolf::getWolfSizeInX()));
	p.x = dist1(gen1);
	std::random_device rd2;
	std::mt19937 gen2(rd2());
	std::uniform_int_distribution<int> dist2(BudgetbarIcon::getRangeMinY(), (BudgetbarIcon::getRangeMaxY() - Wolf::getWolfSizeInY()));
	p.y = dist2(gen2);
	gameWolf = new Wolf(this, p, Wolf::getWolfSizeInX(),Wolf::getWolfSizeInY(), "images\\wolf.jpg");
	gameWolf->draw();
}

void Game::createWarehouse(){
	point WarehouseRef;
	WarehouseRef.x = 0;
	WarehouseRef.y = 100;
	int Pwidth = config.windWidth / 4;
	int Pheight = config.windHeight / 4;
	
	gameWarehouse = new Warehouse(this, WarehouseRef, Pwidth, Pheight, GRAY, BLACK);
	gameWarehouse->draw();
}

void Game::createFoodArea()
{
	point FoodAreaRef;
	FoodAreaRef.x = config.windWidth / 2;
	FoodAreaRef.y = config.windHeight / 2;
	int Height = 50;
	int width = 50;
	gameFoodArea = new FoodArea(this, FoodAreaRef, width, Height, RED, BROWN); // this is a pointer for the game // food area ref : tells x , y
	gameFoodArea->draw();
}
void Game::createBudgetbar()
{
	point budgetbarUpperleft;
	budgetbarUpperleft.x = 0;
	budgetbarUpperleft.y = config.toolBarHeight;

	gameBudgetbar = new Budgetbar(this, budgetbarUpperleft, 0, config.toolBarHeight);
	gameBudgetbar->draw();
}

void Game::createTimer()
{
	gameTimer = new Timer(240000);
}

string Game::modifyTimerToStandard() const
{
	int minutes = gameTimer->remaining() / 60000;
	int seconds = (gameTimer->remaining() % 60000) / 1000;
	string timer_string = to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds);
	return timer_string;
}


void Game::clearBudget() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.bkGrndColor, 1);
	pWind->SetBrush(config.bkGrndColor);
	pWind->DrawRectangle(config.windWidth - 500, config.toolBarHeight, config.windWidth, 2*config.toolBarHeight);
}

void Game::printBudget(string msg) const
{
	clearBudget();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(config.windWidth-200, config.toolBarHeight + 10, msg);

}

void Game::clearStatusBar() const
{
	//Clear Status bar by drawing a filled rectangle
	pWind->SetPen(config.statusBarColor, 1);
	pWind->SetBrush(config.statusBarColor);
	pWind->DrawRectangle(0, config.windHeight - config.statusBarHeight, config.windWidth, config.windHeight);
}

void Game::printMessage(string msg) const
{
	clearStatusBar();	//First clear the status bar

	pWind->SetPen(config.penColor, 50);
	pWind->SetFont(24, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, config.windHeight - (int)(0.85 * config.statusBarHeight), msg);

}

window* Game::getWind() const
{
	return pWind;
}

Farm* Game::getFarm() const
{
	return gameFarm;
}

void Game::go() 
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	int static level = 1;
	bool isExit = false;
	Timer* delay = new Timer(250);
	Timer* wolf_delay = new Timer(10 * 1000);

	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy (CIE101-project) - - - - - - - - - -");
	pWind->DrawString(200, 200, "REAL FILE");

	do
	{
		if (level == 1) {
			if (wolf_delay->check())
			{
				createWolf();
				wolf_delay->setDuration(60 * 1000);
			}
		}
		if (delay->check()) {
			string status_message = "Level: 1, Timer:" + modifyTimerToStandard() + ", Goal: , Current Animal Count: " + to_string(BudgetbarIcon::getAnimalCounter()) + ", Water Amount: " + to_string(WaterIcon::waterAmount());
			printMessage(status_message);
			string budget_string = "BUDGET = $" + to_string(budget);
			printBudget(budget_string);
			redrawFarm();	//Get the coordinates of the user click
			for (int i = 0; i < ChickIcon::count; i++) { ChickIcon::chickList[i]->moveStep(); }
			for (int i = 0; i < CowIcon::count; i++) { CowIcon::cowList[i]->moveStep(); }
			if (gameWolf) {
				gameWolf->moveStep();
			}
			delay->setDuration(500);
		}
		getMouseClick(x, y);
		//if (gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		//{
			//[1] If user clicks on the Toolbar
		if (y >= 0 && y < config.toolBarHeight)
		{
			isExit = gameToolbar->handleClick(x, y);
		}
		else if (y >= config.toolBarHeight && y < 2*config.toolBarHeight)
		{
			isExit = gameBudgetbar->handleClick(x, y);
		}
		//}
		//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	} while (!isExit);
}


