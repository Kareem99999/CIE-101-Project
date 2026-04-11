#include "GameObject.h"
#include "Game.h"
#include "../Config/GameConfig.h"

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
