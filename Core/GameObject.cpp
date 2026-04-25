#include "GameObject.h"
#include "Game.h"
#include "../Config/GameConfig.h"
#include <random>

int Farm::margin = 10;
int Farm::FarmWidth = 10;
int Farm::FarmHeight = 10;
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
FoodArea::FoodArea(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc) : GameObject(r_pGame, ref, r_width, r_height, fc, bc)
{
	FoodAreaWidth = r_width;
	FoodAreaHeight = r_height;
}

void FoodArea::draw() const
{
	window* pWind = pGame->getWind();
	pWind->SetBrush(fillColor);
	pWind->SetPen(borderColor, 4);
	pWind->DrawRectangle(RefPoint.x, RefPoint.y, RefPoint.x + FoodAreaWidth, RefPoint.y + FoodAreaHeight);
}