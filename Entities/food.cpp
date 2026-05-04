#include "Food.h"
#include "../Core/Game.h"
food :: food(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	amount = 0;
	sellprice = 0;
	buyprice = 0;
	name = "";
	foodImagePath = img_path;
}
/*grass::grass(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: food(r_pGame, r_point, r_width, r_height, img_path)
{
	name = "GRASS";
	buyprice = 50;
	sellprice = 0;
	amount = 0;
	
}
void grass::buy()
{
	if (pGame->budget >= buyprice) {
		amount++;
		pGame->budget -= buyprice;
	}
}
void grass::sell()
{
	//TO DO: add code for selling grass here
}
void grass::addFood(int amount)
{
	this->amount += amount;
}
*/
void food::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(foodImagePath, RefPoint.x, RefPoint.y, width, height);
}

eggs::eggs(Game* r_pGame, point r_point, int r_width, int r_height)
	: food(r_pGame, r_point, r_width, r_height, "..\\images\\EGG.jpg")
{
	name = "EGGS";
	buyprice = 0;
	sellprice = 20;
	amount = 0;
	
}
void eggs::addFood(int amount)
{
	this->amount += amount;
}
void eggs::buy()
{
	//TO DO: add code for buying eggs here
}
void eggs :: draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage("images\\EGG.jpeg", RefPoint.x, RefPoint.y, width, height);
}
void eggs::sell()
{
	if (amount > 0)
	{
		amount--;
		pGame->budget += (sellprice);
	}
}



milk::milk(Game* r_pGame, point r_point, int r_width, int r_height)
	: food(r_pGame, r_point, r_width, r_height, "images\\MILK.jpg")
{
	name = "MILK";
	buyprice = 0;
	sellprice = 50;
	amount = 0;
	
}
void milk::addFood(int amount)
{
	this->amount += amount;
}
void milk::buy()
{
	//TO DO: add code for buying milk here
}
void milk:: draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(foodImagePath, RefPoint.x, RefPoint.y, width, height);
}
void milk::sell()
{
	if (amount > 0)
	{
		amount--;
		pGame->budget += sellprice;
	}
}
// to do see wtf is the addBugdet function and if not there do it