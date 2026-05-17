#include "Budgetbar.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include "../Core/GameObject.h"
#include "../Entities/Animal.h"
#include <iostream>
#include <fstream>
using namespace std;

int BudgetbarIcon::AnimalsCounter = 0;
int ChickIcon::count = 0;
int CowIcon::count = 0;
int ChickIcon::cost = 100;
int CowIcon::cost = 1000;
int WaterIcon::cost = 20;
Chick** ChickIcon::chickList = nullptr;
Cow** CowIcon::cowList = nullptr;
FoodArea** WaterIcon::FoodAreaList = nullptr;
int WaterIcon::amount = 0;
int BudgetbarIcon::range_min_x = 50;
int BudgetbarIcon::range_max_x = config.windWidth - 50;
int BudgetbarIcon::range_min_y = (config.toolBarHeight * 2) + 50;
int BudgetbarIcon::range_max_y = config.windHeight - config.statusBarHeight - 50;
BudgetbarIcon::BudgetbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
}

void BudgetbarIcon::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
}

int BudgetbarIcon::getAnimalCounter()
{
	return AnimalsCounter;
}

void BudgetbarIcon::setAnimalCounter(int value)
{
	AnimalsCounter = value;
}

void BudgetbarIcon::increaseAnimals()
{
	AnimalsCounter++;
}

void BudgetbarIcon::setRangeMinX(int valueMinX)
{
	range_min_x = valueMinX;
}
void BudgetbarIcon::setRangeMaxX(int valueMaxX)
{
	range_max_x = valueMaxX;
}
void BudgetbarIcon::setRangeMinY(int valueMinY)
{
	range_min_y = valueMinY;
}
void BudgetbarIcon::setRangeMaxY(int valueMaxY)
{
	range_max_y = valueMaxY;
}
int  BudgetbarIcon::getRangeMinX()
{
	return range_min_x;
}
int  BudgetbarIcon::getRangeMaxX()
{
	return range_max_x;
}
int  BudgetbarIcon::getRangeMinY()
{
	return range_min_y;
}
int  BudgetbarIcon::getRangeMaxY()
{
	return range_max_y;
}
ChickIcon::ChickIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : BudgetbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
	chickList = new Chick * [15];
	for (int i = 0; i < 15; i++) {
		chickList[i] = nullptr;
	}
}

void ChickIcon::setIconProperties()
{
	window* pWind = pGame->getWind();
	pWind->SetFont(16, BOLD, BY_NAME, "Arial");
	pWind->SetPen(BLACK, 1);
	pWind->DrawString(RefPoint.x, RefPoint.y + (config.toolBarHeight - 15), "$" + to_string(cost));
	pWind->DrawString(RefPoint.x + config.iconWidth - 20, RefPoint.y, to_string(count));
}

CowIcon::CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : BudgetbarIcon(r_pGame, r_point, r_width, r_height, img_path)
{
	cowList = new Cow * [15];
	for (int i = 0; i < 15; i++) {
		cowList[i] = nullptr;
	}
}

void CowIcon::setIconProperties()
{
	window* pWind = pGame->getWind();
	pWind->SetFont(16, BOLD, BY_NAME, "Arial");
	pWind->SetPen(BLACK, 1);
	pWind->DrawString(RefPoint.x, RefPoint.y + (config.toolBarHeight - 15), "$" + to_string(cost));
	pWind->DrawString(RefPoint.x + config.iconWidth - 20, RefPoint.y, to_string(count));
}


void ChickIcon::onClick()
{
	//TO DO: add code for cleanup and game exit here
	/*
	//draw image of this object in the field
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
	*/
	//Chick* new_chick = new Chick(pGame, RefPoint, 30, 30, "images\\Chick.png");
	cout << "Icon Chick Clicked" << endl;
	if (pGame->budget >= cost && count < 15) {
		pGame->budget -= cost;
		BudgetbarIcon::increaseAnimals();
		pGame->clearBudget();
		string budget_string = "BUDGET = $" + to_string(pGame->budget);
		pGame->printBudget(budget_string);

		point p;
		// 1. Obtain a seed from a non-deterministic source (if available)
		std::random_device rd1;

		// 2. Seed the Mersenne Twister engine
		// std::mt19937 is a high-quality pseudo-random number generator
		std::mt19937 gen1(rd1());
		std::uniform_int_distribution<int> dist1(range_min_x, (range_max_x - Chick::getChickSizeInX()));
		p.x = dist1(gen1);
		//std::cout << "P.X = " << p.x << endl;
		// 1. Obtain a seed from a non-deterministic source (if available)
		std::random_device rd2;

		// 2. Seed the Mersenne Twister engine
		// std::mt19937 is a high-quality pseudo-random number generator
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<int> dist2(range_min_y, (range_max_y - Chick::getChickSizeInY()));
		p.y = dist2(gen2);
		for (int i = 0; i < 15; i++) {
			if (!chickList[i]) {
				chickList[count] = new Chick(pGame, p, Chick::getChickSizeInX(), Chick::getChickSizeInY(), image_path);
				chickList[count]->draw();
				count++;
				break;
			}
		}
	}
	else if (count >= 15) {
		pGame->printMessage("You have reached the maximum number of chicks!");
	}
	else {
		pGame->printMessage("Not enough budget to buy a chick!");
	}
}

void CowIcon::onClick()
{
	cout << "Icon Cow Clicked" << endl;
	if (pGame->budget >= cost && count < 15) {
		pGame->budget = pGame->budget - cost;
		BudgetbarIcon::increaseAnimals();
		pGame->clearBudget();
		string budget_string = "BUDGET = $" + to_string(pGame->budget);
		pGame->printBudget(budget_string);

		point p;
		std::random_device rd1;
		std::mt19937 gen1(rd1());
		std::uniform_int_distribution<int> dist1(range_min_x, (range_max_x - Cow::getCowSizeInX()));
		p.x = dist1(gen1);
		std::random_device rd2;
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<int> dist2(range_min_y, (range_max_y - Cow::getCowSizeInY()));
		p.y = dist2(gen2);
		for (int i = 0; i < 15; i++) {
			if (!cowList[i]) {
				cowList[count] = new Cow(pGame, p, Cow::getCowSizeInX(), Cow::getCowSizeInY(), image_path);
				cowList[count]->draw();
				count++;
				break;
			}
		}
	}
	else if (count >= 15) {
		pGame->printMessage("You have reached the maximum number of cows!");
	}
	else {
		pGame->printMessage("Not enough budget to buy a cow!");
	}
}

void ChickIcon::changeChickCount(int value)
{
	count += value;
}

void CowIcon::changeCowCount(int value)
{
	count += value;
}

void ChickIcon::Saving(ofstream& saveFile) const
{
	saveFile << "CHICKS " << count << "\n";
	int counter = 0;
	for (int i = 0; i < count; i++) {
		if (chickList[i]) {
			saveFile << chickList[i]->curr_pos.x << " " << chickList[i]->curr_pos.y << " " << chickList[i]->curr_vel.x << " " << chickList[i]->curr_vel.y 
				<< " " << chickList[i]->getFoodeaten() << " " << chickList[i]->getPrevColl() << " " << chickList[i]->getCurrColl() << "\n";
			counter++;
		}
		if (counter >= count) { break; }
	}
}

void ChickIcon::Loading(ifstream& loadFile) const
{
	string key;
	loadFile >> key >> count;
	for (int i = 0; i < count; i++) {
		int x, y, velx, vely, food;
		bool prevColl, currColl;
		loadFile >> x >> y >> velx >> vely >> food >> prevColl >> currColl;
		chickList[i] = new Chick(pGame, {x, y}, Chick::getChickSizeInX(), Chick::getChickSizeInY(), "images\\chick.jpg");
		chickList[i]->curr_vel = {velx, vely};
		chickList[i]->setFoodeaten(food);
		chickList[i]->setColl(prevColl, currColl);
	}
}

void CowIcon::Saving(ofstream& saveFile) const
{
	saveFile << "COWS " << count << "\n";
	int counter = 0;
	for (int i = 0; i < count; i++) {
		if (cowList[i]) {
			saveFile << cowList[i]->curr_pos.x << " " << cowList[i]->curr_pos.y << " " << cowList[i]->curr_vel.x << " " 
				<< cowList[i]->curr_vel.y << " " << cowList[i]->getFoodeaten() << " " << cowList[i]->getPrevColl() << " " << cowList[i]->getCurrColl() << "\n";
			counter++;
		}
		if (counter >= count) { break; }
	}
}

void CowIcon::Loading(ifstream& loadFile) const
{
	string key;
	loadFile >> key >> count;
	for (int i = 0; i < count; i++) {
		int x, y, velx, vely, food;
		bool prevColl, currColl;
		loadFile >> x >> y >> velx >> vely >> food >> prevColl >> currColl;
		cowList[i] = new Cow(pGame, {x, y}, Cow::getCowSizeInX(), Cow::getCowSizeInY(), "images\\cow.jpg");
		cowList[i]->curr_vel = {velx, vely};
		cowList[i]->setFoodeaten(food);
		cowList[i]->setColl(prevColl, currColl);
	}
}

Budgetbar::Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height) : Drawable(r_pGame, r_point, r_width, r_height)
{
	//First prepare List of images for each icon
	//To control the order of these images in the menu, reoder them in enum ICONS above	
	iconsImages[ICON_CHICK] = "images\\chick.jpg";
	iconsImages[ICON_WATER] = "images\\well.jpg";
	iconsImages[ICON_COW] = "images\\cow.jpg";

	point p;
	p.x = 0;
	p.y = config.toolBarHeight;

	iconsList = new BudgetbarIcon * [BUDGET_ICON_COUNT];

	//For each icon in the tool bar create an object 
	iconsList[ICON_CHICK] = new ChickIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_CHICK]);
	p.x += config.iconWidth;
	iconsList[ICON_COW] = new CowIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_COW]);
	p.x += config.iconWidth;
	iconsList[ICON_WATER] = new WaterIcon(pGame, p, config.iconWidth, config.toolBarHeight, iconsImages[ICON_WATER]);
	p.x += config.iconWidth;
	}

Budgetbar::~Budgetbar()
{
	for (int i = 0; i < 15; i++)
		if (ChickIcon::chickList[i]) delete ChickIcon::chickList[i];

	delete[] ChickIcon::chickList;

	for (int i = 0; i < 15; i++)
		if (CowIcon::cowList[i]) delete CowIcon::cowList[i];

	delete[] CowIcon::cowList;

	ChickIcon::count = 0;
	CowIcon::count = 0;

	for (int i = 0; i < 50; i++) {
		if (WaterIcon::FoodAreaList[i]) {
			delete WaterIcon::FoodAreaList[i];
		}
	}
	delete[] WaterIcon::FoodAreaList;
	WaterIcon::amount = 0;
	BudgetbarIcon::setAnimalCounter(0);

	for (int i = 0; i < BUDGET_ICON_COUNT; i++)
		delete iconsList[i];

	delete[] iconsList;
}

void Budgetbar::draw() const
{
	for (int i = 0; i < BUDGET_ICON_COUNT; i++) { 
		iconsList[i]->draw(); 
		iconsList[i]->setIconProperties();
	}
	window* pWind = pGame->getWind();
	pWind->SetPen(BLACK, 3);
	pWind->DrawLine(0, 2*config.toolBarHeight, pWind->GetWidth(), 2*config.toolBarHeight);
}

BudgetbarIcon* Budgetbar::getIcon(int iconIndex) const
{
	if (iconIndex < 0 || iconIndex >= BUDGET_ICON_COUNT)
		return nullptr;	//invalid index
	return iconsList[iconIndex];
}

bool Budgetbar::handleClick(int x, int y)
{
	if (x > BUDGET_ICON_COUNT * config.iconWidth)	//click outside toolbar boundaries
		return false;


	//Check whick icon was clicked
	//==> This assumes that menu icons are lined up horizontally <==
	//Divide x co-ord of the point clicked by the icon width (int division)
	//if division result is 0 ==> first icon is clicked, if 1 ==> 2nd icon and so on

	int clickedIconIndex = (x / config.iconWidth);
	iconsList[clickedIconIndex]->onClick();	//execute onClick action of clicled icon

	//if (clickedIconIndex == ICON_EXIT) return true;

	return false;

}

// ####################++++++++++----------Water thingies----------++++++++++####################
WaterIcon::WaterIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: BudgetbarIcon(r_pGame, r_point, r_width, r_height, img_path) {
	FoodAreaList = new FoodArea * [50];
	for (int i = 0; i < 50; i++) {
		FoodAreaList[i] = nullptr;
	}
	amount = 0;
	WaterIcon::cost = 20;
}

void WaterIcon::increasewater()
{
	amount++;
}


void WaterIcon::setIconProperties()
{
	window* pWind = pGame->getWind();
	pWind->SetFont(16, BOLD, BY_NAME, "Arial");
	pWind->SetPen(BLACK, 1);
	pWind->DrawString(RefPoint.x, RefPoint.y + (config.toolBarHeight - 15), "$" + to_string(cost));
	pWind->DrawString(RefPoint.x + config.iconWidth - 20, RefPoint.y, to_string(amount));
}

void WaterIcon::Saving(ofstream& saveFile) const
{
	int counter = 0;
	saveFile << "FOODAREAS " << amount << "\n";
	for (int i = 0; i < 50; i++) {
		if (FoodAreaList[i]) {
			saveFile << FoodAreaList[i]->getFoodAreaRef().x << " " << FoodAreaList[i]->getFoodAreaRef().y << " " << FoodAreaList[i]->getfoodcounter() << "\n";
			counter++;
		}
		if (counter >= amount) { break; }
	}
}

void WaterIcon::Loading(ifstream& loadFile) const
{
	string key;
	loadFile >> key >> amount;
	for (int i = 0; i < amount; i++) {
		int x, y, food;
		loadFile >> x >> y >> food;
		FoodAreaList[i] = new FoodArea(pGame, {x, y});
		FoodAreaList[i]->decreaseFood(3 - food);
		FoodAreaList[i]->draw();
	}
}

int WaterIcon::waterAmount()
{
	return amount;
}

void WaterIcon::decreaseWater()
{
	if (amount > 0) {
		amount--;
	}
}

void WaterIcon::onClick()
{
		cout << "Icon Water Clicked" << endl;
		if (pGame->budget >= cost && amount < 50) {
			pGame->budget -= cost;

			point p;
			std::random_device rd1;
			std::mt19937 gen1(rd1());
			std::uniform_int_distribution<int> dist1(range_min_x, (range_max_x - FoodArea::getFoodAreaX()));
			p.x = dist1(gen1);
			std::random_device rd2;
			std::mt19937 gen2(rd2());
			std::uniform_int_distribution<int> dist2(range_min_y, (range_max_y - FoodArea::getFoodAreaY()));
			p.y = dist2(gen2);
			for (int i = 0; i < 50; i++) {
				if (!FoodAreaList[i]) {
					FoodAreaList[amount] = new FoodArea(pGame, p);
					FoodAreaList[amount]->draw();
					amount++;
					break;
				}
			}
			pGame->clearBudget();
			string budget_string = "BUDGET = $" + to_string(pGame->budget);
			pGame->printBudget(budget_string);
			string msg = "Water amount = " + to_string(amount);
			cout << msg << endl;
		}
		else if (amount >= 50) {
			pGame->printMessage("You have reached the maximum number of food areas!");
		}
		else {
			pGame->printMessage("Not enough budget to buy a food area!");
		}
}