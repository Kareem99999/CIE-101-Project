#include "GameObject.h"
#include "Game.h"
#include "../Config/GameConfig.h"
#include <random>
#include <iostream>

int Farm::margin = 10;
int Farm::FarmWidth = 10;
int Farm::FarmHeight = 10;
int FoodArea::FoodAreaWidth = 50;
int FoodArea::FoodAreaHeight = 50;
GameObject::GameObject(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc) : Drawable (r_pGame, ref, r_width, r_height)
{
	fillColor = fc;
	borderColor = bc;
}

void GameObject::setRefPoint(point p)
{
	RefPoint = p;
}

// you should implement this function knowing that each game object has refPoint, width and height 
// for simplicity, you can consider all game objects are rectangles
bool GameObject::CollisionDetection(const GameObject& gObj)
{
	return false;
}

Farm::Farm(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc) : GameObject(r_pGame, ref, r_width, r_height, fc, bc){
	FarmWidth = r_width;
	FarmHeight = r_height;
	setRefPoint(ref);
}

void Farm::draw() const {
	window* pWind = pGame->getWind();
	pWind->SetBrush(fillColor);
	pWind->SetPen(borderColor, 4);
	pWind->DrawRectangle(RefPoint.x, RefPoint.y, RefPoint.x + FarmWidth, RefPoint.y + FarmHeight);
};

int Farm::getMargin()
{
	return margin;
}

int Farm::getFarmWidth()
{
	return FarmWidth;
}

int Farm::getFarmHeight()
{
	return FarmHeight;
}

void Farm::keepInFarm(point& position, point& velocity, point dimensions, int maxVelo, int minVelo)
{
	static thread_local std::mt19937 gen{ std::random_device{}() };
	if (position.x + dimensions.x + margin >= FarmWidth + RefPoint.x) {
		position.x -= velocity.x;
		std::uniform_int_distribution<int> direc(minVelo, maxVelo);
		velocity.x = -direc(gen);
	}
	else if (position.x - margin <= RefPoint.x) {
		position.x -= velocity.x;
		std::uniform_int_distribution<int> direc(minVelo, maxVelo);
		velocity.x = direc(gen);
	}
	if (position.y + dimensions.y + margin >= FarmHeight + RefPoint.y) {
		position.y -= velocity.y;
		std::uniform_int_distribution<int> direc(minVelo, maxVelo);
		velocity.y = -direc(gen);
	}
	else if (position.y - margin <= RefPoint.y) {
		position.y -= velocity.y;
		std::uniform_int_distribution<int> direc(minVelo, maxVelo);
		velocity.y = direc(gen);
	}
}

Warehouse::Warehouse(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc) : GameObject(r_pGame, ref, r_width, r_height, fc, bc) {
	WarehouseWidth = r_width;
	WarehouseHeight = r_height;
};

void Warehouse::draw() const
{
	window* pWind = pGame->getWind();
	pWind->SetBrush(fillColor);
	pWind->SetPen(borderColor, 4);
	pWind->DrawRectangle(RefPoint.x, RefPoint.y, RefPoint.x + WarehouseWidth, RefPoint.y + WarehouseHeight);
};

int Warehouse::getWarehouseWidth() { return WarehouseWidth; }
int Warehouse::getWarehouseHeight() { return WarehouseHeight; }
point Warehouse::getRefPoint() { return RefPoint; }

void Warehouse::onClick() {
	window* WarehouseWind;
	WarehouseWind = pGame->CreateWind(config.windWidth, config.windHeight, config.wx, config.wy);
	/*try {
		WarehouseWind->DrawImage("EGG.jpg", 0.17 * config.windWidth, 0.2 * config.windHeight, 0.25 * config.windWidth, 0.25 * config.windHeight);
		WarehouseWind->DrawImage("MILK.jpg", 0.58 * config.windWidth, 0.2 * config.windHeight, 0.25 * config.windWidth, 0.25 * config.windHeight);
	}
	catch (...) {}
	*/
	WarehouseWind->SetPen(BLACK, 4);
	WarehouseWind->SetFont(24, BOLD, BY_NAME, "Arial");
	WarehouseWind->DrawString(.17 * config.windWidth, 0.55 * config.windHeight, "Eggs price: 100$");
	WarehouseWind->DrawString(.58 * config.windWidth, 0.55 * config.windHeight, "Milk price: 200$");
	WarehouseWind->SetBrush(PURPLE);
	WarehouseWind->DrawRectangle(.17 * config.windWidth, 0.8 * config.windHeight, .42 * config.windWidth, .85 * config.windHeight);
	WarehouseWind->DrawRectangle(.58 * config.windWidth, 0.8 * config.windHeight, .83 * config.windWidth, .85 * config.windHeight);
	WarehouseWind->DrawString(.26 * config.windWidth, 0.81 * config.windHeight, "Sell Eggs");
	WarehouseWind->DrawString(.670 * config.windWidth, 0.81 * config.windHeight, "Sell Milk");
	WarehouseWind->DrawRectangle(0, 0, 0.1 * config.windWidth, 0.1 * config.windHeight);
	WarehouseWind->DrawString(0.035 * config.windWidth, 0.03 * config.windHeight, "Exit");
	while (WarehouseWind) {
		WarehouseWind->SetPen(BLACK, 4);
		WarehouseWind->DrawString(.17 * config.windWidth, 0.6 * config.windHeight, "Count:" + to_string(pGame->getEggcount()));
		WarehouseWind->DrawString(.58 * config.windWidth, 0.6 * config.windHeight, "Count:" + to_string(pGame->getMilkcount()));
		int x, y;
		WarehouseWind->GetMouseClick(x, y);
		if (x >= .17 * config.windWidth && x <= .42 * config.windWidth && y >= 0.8 * config.windHeight && y <= 0.85 * config.windHeight) {
			if (pGame->getEggcount() > 0) {
				pGame->budget += 100;
				pGame->decreaseeggscount();
				WarehouseWind->SetBrush(config.bkGrndColor);
				WarehouseWind->SetPen(config.bkGrndColor, 1);
				WarehouseWind->DrawRectangle(.17 * config.windWidth, 0.6 * config.windHeight, .7 * config.windWidth, .7 * config.windHeight);
			}
		}
		else if (x >= .58 * config.windWidth && x <= .83 * config.windWidth && y >= 0.8 * config.windHeight && y <= 0.85 * config.windHeight) {
			if (pGame->getMilkcount() > 0) {
				pGame->budget += 200;
				pGame->decreasemilkcount();
				WarehouseWind->SetBrush(config.bkGrndColor);
				WarehouseWind->SetPen(config.bkGrndColor, 1);
				WarehouseWind->DrawRectangle(.17 * config.windWidth, 0.6 * config.windHeight, .7 * config.windWidth, .7 * config.windHeight);
			}
		}
		else if (x >= 0 && x <= .1 * config.windWidth && y >= 0 && y <= .1 * config.windHeight) {
			delete WarehouseWind;
			WarehouseWind = nullptr;
			break;
		}
	}
}

FoodArea::FoodArea(Game* r_pGame, point ref) : GameObject(r_pGame, ref, 50, 50, GREEN, GREEN)
{}

void FoodArea::draw() const
{
	window* pWind = pGame->getWind();
	pWind->SetBrush(fillColor);
	pWind->SetPen(borderColor, 4);
	pWind->DrawRectangle(RefPoint.x, RefPoint.y, RefPoint.x + FoodAreaWidth, RefPoint.y + FoodAreaHeight);
	pWind->SetPen(BLACK, 4);
	pWind->DrawString(RefPoint.x + FoodAreaWidth / 2 - 7, RefPoint.y + FoodAreaHeight / 2 - 12, to_string(foodcounter));
}

int FoodArea::getFoodAreaX() { return FoodAreaWidth; }
int FoodArea::getFoodAreaY() { return FoodAreaHeight; }

point FoodArea::getFoodAreaRef()
{
	return RefPoint;
}

void FoodArea::decreaseFood(int x) { foodcounter -= x; }
int FoodArea::getfoodcounter() {return foodcounter;};
