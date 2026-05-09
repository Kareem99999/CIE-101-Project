#include "Game.h"
#include "../Config/GameConfig.h"
#include "GameObject.h"
#include "../UI/BudgetBar.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
using namespace std;

bool Game::shouldLoad = false;
Game::Game()
{
	pWind = CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);
	createToolbar();
	createBudgetbar();
	createWarehouse();
	createFarm();
	clearStatusBar();
	createTimer();
	gameWolf = nullptr;
	ispaused = false;
	wolf_delay = new Timer(20 * 1000);

	if (shouldLoad) {
		shouldLoad = false;
		ifstream SaveFile("SaveFile.txt");
		if (SaveFile) {
			int currentTime, animalCount;
			SaveFile >> budget >> currentTime >> animalCount;
			gameTimer->setDuration(currentTime);
			BudgetbarIcon::setAnimalCounter(animalCount);
			for (int i = 0; i < BUDGET_ICON_COUNT; i++) {
				gameBudgetbar->getIcon(i)->Loading(SaveFile);
			}
		}
		SaveFile.close();
		printMessage("Game Loaded!");
	}
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
	pausedTime = std::chrono::milliseconds(0);
	isPaused = false;  // Force reset
}

bool Timer::check() const {
	auto now = TIMER::now();
	bool expired = (now >= end);
	if (expired) {
		auto remaining_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - now).count();
		cout << "CHECK: expired=true, remaining=" << remaining_ms << "ms, end time=" << end.time_since_epoch().count() << ", now=" << now.time_since_epoch().count() << endl;
	}
	return expired;
}

long long Timer::elapsed() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(TIMER::now() - start).count();
}

long long Timer::remaining() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - TIMER::now()).count();
}
void Timer::paused() {
	if (!isPaused) {
		isPaused = true;
		pauseStart = TIMER::now();
	}
}
void Timer::resume() {
	if (isPaused) {
		isPaused = false;
		pausedTime += std::chrono::duration_cast<std::chrono::milliseconds>(TIMER::now() - pauseStart);
		end += std::chrono::duration_cast<std::chrono::milliseconds>(TIMER::now() - pauseStart);
	}
}
Game::~Game()
{
	for (int i = 0; i < eggsCounter; i++) delete gameEggslist[i];
	delete[] gameEggslist;
	for (int i = 0; i < milkCounter; i++) delete gameMilklist[i];
	delete[] gameMilklist;
	delete gameToolbar;
	delete gameBudgetbar;
	delete gameFarm;
	delete gameWarehouse;
	delete gameTimer;
	delete gameWolf;
	pWind->SetWaitClose(false);
	delete pWind;
	delete wolf_delay;
}

clicktype Game::getMouseClick(int& x, int& y) const
{
	return pWind->GetMouseClick(x, y);	//Wait for mouse click

}

void Game::decreaseeggscount() { eggsCounter--; }

void Game::decreasemilkcount() { milkCounter--; }

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
	for (int i = 0; i < WaterIcon::waterAmount(); i++) if ( WaterIcon::FoodAreaList[i] != nullptr) WaterIcon::FoodAreaList[i]->draw();
	gameWarehouse->draw();
}

void Game::createWolf()
{
	if (gameWolf != nullptr) return;
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

int Game::getEggcount() {
	return eggsCounter;
}

int Game::getMilkcount() {
	return milkCounter;
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

void Game::saving() const{
	ofstream SaveFile("SaveFile.txt");
	SaveFile << budget << " " << gameTimer->remaining() << " " << BudgetbarIcon::getAnimalCounter() << "\n";
	for (int i = 0; i < BUDGET_ICON_COUNT; i++) {
		gameBudgetbar->getIcon(i)->Saving(SaveFile);
		SaveFile << "\n";
	}
	SaveFile.close();
	printMessage("Game Saved!");
}

void Game::startLoading() {
	shouldLoad = true;
	
}

void Game::restart() {
	timeToRestart = true;
}

bool Game::go()
{
	//This function reads the position where the user clicks to determine the desired operation
	int x, y;
	cout << "gameWolf = " << gameWolf << endl;
	int static level = 1;
	bool isExit = false;
	bool pausewindow = false;
	gameEnded = false;
	Timer delay(300);
	//Change the title
	pWind->ChangeTitle("- - - - - - - - - - Farm Frenzy (CIE101-project) - - - - - - - - - -");
	pWind->DrawString(200, 200, "REAL FILE");

	do
	{
		if (!ispaused && !gameEnded && gameTimer->remaining() > 0) {
			pausewindow = false;
			if (level == 1) {
				if (wolf_delay->check())
				{
					createWolf();

					wolf_delay->setDuration(60 * 1000);
				}
			}
			if (timeToRestart) { return true; }
			if (delay.check()) {
				string status_message = "Level: 1, Timer:" + modifyTimerToStandard() + ", Goal: , Current Animal Count: " + to_string(BudgetbarIcon::getAnimalCounter()) + ", Water Amount: " + to_string(WaterIcon::waterAmount());
				printMessage(status_message);
				string budget_string = "BUDGET = $" + to_string(budget);
				printBudget(budget_string);
				redrawFarm();
				for (int i = 0; i < totalcreatedeggs; i++) {
					if (gameEggslist[i]) {
						gameEggslist[i]->draw();
					}
				}
				for (int i = 0; i < totalcreatedmilk; i++) {
					if (gameMilklist[i]) {
						gameMilklist[i]->draw();
					}
				}
				for (int i = 0; i < ChickIcon::count; i++) {
					ChickIcon::chickList[i]->moveStep();
					ChickIcon::chickList[i]->ifColl();
					for (int x = 0; x < WaterIcon::waterAmount(); x++) {
						if (WaterIcon::FoodAreaList[x] && WaterIcon::FoodAreaList[x]->getfoodcounter() <= 0) {
							delete WaterIcon::FoodAreaList[x];
							WaterIcon::FoodAreaList[x] = nullptr;
						}
					}
					if (ChickIcon::chickList[i]->getFoodeaten() != 0 && ChickIcon::chickList[i]->getFoodeaten() % 2 == 0) {
						gameEggslist[totalcreatedeggs] = new eggs(this, ChickIcon::chickList[i]->curr_pos, 20, 20);
						gameEggslist[totalcreatedeggs]->draw();
						totalcreatedeggs++;
						eggsCounter++;
						ChickIcon::chickList[i]->Resetfoodeaten();
					}
				}
				for (int i = 0; i < CowIcon::count; i++) {
					CowIcon::cowList[i]->moveStep();
					CowIcon::cowList[i]->ifColl();
					for (int x = 0; x < WaterIcon::waterAmount(); x++) {
						if (WaterIcon::FoodAreaList[x] && WaterIcon::FoodAreaList[x]->getfoodcounter() <= 0) {
							delete WaterIcon::FoodAreaList[x];
							WaterIcon::FoodAreaList[x] = nullptr;
						}
					}
					if (CowIcon::cowList[i]->getFoodeaten() != 0 && CowIcon::cowList[i]->getFoodeaten() % 4 == 0) {
						gameMilklist[totalcreatedmilk] = new milk(this, CowIcon::cowList[i]->curr_pos, 20, 20);
						gameMilklist[totalcreatedmilk]->draw();
						totalcreatedmilk++;
						milkCounter++;
						CowIcon::cowList[i]->Resetfoodeaten();
					}
				}
				if (gameWolf) {
					gameWolf->moveStep();
				}
				delay.setDuration(300);
			}
		}
		getMouseClick(x, y);
		if (x >= gameWarehouse->getRefPoint().x && x <= gameWarehouse->getRefPoint().x + gameWarehouse->getWarehouseWidth() && y >= gameWarehouse->getRefPoint().y && y <= gameWarehouse->getRefPoint().y + gameWarehouse->getWarehouseWidth()) {
			gameWarehouse->onClick();
		}
		//if (gameMode == MODE_DSIGN)		//Game is in the Desgin mode
		//{
			//[1] If user clicks on the Toolbar
		if (y >= 0 && y < config.toolBarHeight)
		{
			isExit = gameToolbar->handleClick(x, y);
		}
		else if (y >= config.toolBarHeight && y < 2 * config.toolBarHeight)
		{
			isExit = gameBudgetbar->handleClick(x, y);
		}
		//}
		if (ispaused && pausewindow == false)
		{
			int centerX = config.windWidth / 2;
			int centerY = config.windHeight / 2;
			int width = 350;
			int height = 120;
			int left = centerX - width / 2;
			int top = centerY - height / 2;

			pWind->SetPen(color(50, 50, 50), 1);
			pWind->SetBrush(color(40, 40, 40));
			pWind->DrawRectangle(left + 8, top + 8, left + width + 8, top + height + 8, FILLED, 15, 15);


			pWind->SetPen(color(100, 100, 200), 3);
			pWind->SetBrush(color(30, 30, 60));
			pWind->DrawRectangle(left, top, left + width, top + height, FILLED, 15, 15);

			pWind->SetFont(40, BOLD, BY_NAME, "Arial");
			pWind->SetPen(color(255, 100, 100), 1);
			pWind->DrawString(centerX - 80, centerY - 15, "PAUSED");
			pausewindow = true;
		}
		if (gameTimer->remaining() <= 0 && !gameEnded && budget < 50000)
		{
			gameEnded = true;
			{
				int centerX = config.windWidth / 2;
				int centerY = config.windHeight / 2;

				pWind->SetPen(RED, 3);
				pWind->SetBrush(DARKGRAY);
				pWind->DrawRectangle(centerX - 150, centerY - 60, centerX + 150, centerY + 60, FILLED);

				pWind->SetFont(40, BOLD, BY_NAME, "Arial");
				pWind->SetPen(RED, 1);
				pWind->DrawString(centerX - 100, centerY - 20, "GAME OVER");
				int clickX, clickY;
				getMouseClick(clickX, clickY);

			}
		}
	} while (!isExit);

		return !isExit;
	}


