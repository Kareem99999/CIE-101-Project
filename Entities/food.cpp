#include "Food.h"
#include "../Core/Game.h"
#include <fstream>

int food::sellprice = 0;
food :: food(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	amount = 0;
	sellprice = 0;
	name = "";
	foodImagePath = img_path;
}

eggs::eggs(Game* r_pGame, point r_point, int r_width, int r_height)
	: food(r_pGame, r_point, r_width, r_height, "images\\EGG.jpg")
{
	name = "EGGS";
	sellprice = 50;
	amount = 0;
	
}
void eggs::addFood(int amount)
{
	this->amount += amount;
}
void eggs :: draw() const
{
	if (!enableDrawing) return;
	window* pWind = pGame->getWind();
	pWind->DrawImage("images\\EGG.jpeg", RefPoint.x, RefPoint.y, width, height);
}
int eggs::getsellPrice()
{
	return sellprice;
}

void eggs::onClick(int posX, int posY)
{
	if (posX >= RefPoint.x && posX <= RefPoint.x + 20 && posY >= RefPoint.y && posY <= RefPoint.y + 20 && enableDrawing)
	{
		enableDrawing = false;
		pGame->changeEggcount();
	}
}

void eggs::Saving(ofstream& saveFile) const
{
	saveFile << RefPoint.x << " " << RefPoint.y << " " << enableDrawing << "\n";
}

void eggs::LoadEnability(bool enable)
{
	enableDrawing = enable;
}

milk::milk(Game* r_pGame, point r_point, int r_width, int r_height)
	: food(r_pGame, r_point, r_width, r_height, "images\\MILK.jpg")
{
	name = "MILK";
	sellprice = 500;
	amount = 0;
	
}

void milk::onClick(int posX, int posY)
{
	if (posX >= RefPoint.x && posX <= RefPoint.x + 20 && posY >= RefPoint.y && posY <= RefPoint.y + 20 && enableDrawing)
	{
		enableDrawing = false;
		pGame->changeMilkcount();
	}
}
void milk::addFood(int amount)
{
	this->amount += amount;
}
void milk:: draw() const
{
	if (!enableDrawing) return;
	window* pWind = pGame->getWind();
	pWind->DrawImage(foodImagePath, RefPoint.x + Cow::getCowSizeInX(), RefPoint.y, width, height);
}
int milk::getsellPrice()
{
	return sellprice;
}

void milk::Saving(ofstream& saveFile) const
{
	saveFile << RefPoint.x << " " << RefPoint.y << " " << enableDrawing << "\n";
}
void milk::LoadEnability(bool enable)
{
	enableDrawing = enable;
}

// to do see wtf is the addBugdet function and if not there do it