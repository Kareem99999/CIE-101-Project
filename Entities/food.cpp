#include "Food.h"
#include "../Core/Game.h"
#include <fstream>

int food::sellprice = 0;
food :: food(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	amount = 0;
	sellprice = 0;
	foodImagePath = img_path;
	appearingTimer = new Durations(8 * 1000);
}

Durations::Durations(int duration) {
	start = TIMER::now();
	end = start + std::chrono::milliseconds(duration);
}

void Durations::setDuration(int Duration) {
	start = TIMER::now();
	end = start + std::chrono::milliseconds(Duration);
}

bool Durations::checkEnd() const {
	auto now = TIMER::now();
	bool expired = (now >= end);
	if (expired) {
		auto remaining_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - now).count();
	}
	return expired;
}

double Durations::remainingInSeconds() const {
	return -1 > ((std::chrono::duration_cast<std::chrono::milliseconds>(end - TIMER::now()).count()) / 1000) ? -1 : ((std::chrono::duration_cast<std::chrono::milliseconds>(end - TIMER::now()).count()) / 1000);
}

eggs::eggs(Game* r_pGame, point r_point, int r_width, int r_height)
	: food(r_pGame, r_point, r_width, r_height, "images\\EGG.jpg")
{
	sellprice = 50;
	amount = 0;
	appearingTimer = new Durations(8 * 1000);
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
	if (posX >= RefPoint.x && posX <= RefPoint.x + 20 && posY >= RefPoint.y && posY <= RefPoint.y + 20 && enableDrawing 
		&& (pGame->getEggcount() + pGame->getMilkcount()) < Warehouse::getStorageLimit())
	{
		enableDrawing = false;
		pGame->changeEggcount();
	}
}

void eggs::Saving(ofstream& saveFile) const
{
	saveFile << RefPoint.x << " " << RefPoint.y << " " << enableDrawing << " " << appearingTimer->remainingInSeconds() << "\n";
}

void eggs::LoadEnability(bool enable)
{
	enableDrawing = enable;
}

bool eggs::isEnableDrawing() const
{
	return enableDrawing;
}

milk::milk(Game* r_pGame, point r_point, int r_width, int r_height)
	: food(r_pGame, r_point, r_width, r_height, "images\\MILK.jpg")
{
	sellprice = 500;
	amount = 0;
	appearingTimer = new Durations(8 * 1000);
}

void milk::onClick(int posX, int posY)
{
	if (posX >= RefPoint.x && posX <= RefPoint.x + 20 && posY >= RefPoint.y && posY <= RefPoint.y + 20 && enableDrawing 
		&& (pGame->getEggcount() + pGame->getMilkcount()) < Warehouse::getStorageLimit())
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
	saveFile << RefPoint.x << " " << RefPoint.y << " " << enableDrawing << " " << appearingTimer->remainingInSeconds() << "\n";
}
void milk::LoadEnability(bool enable)
{
	enableDrawing = enable;
}

bool milk::isEnableDrawing() const
{
	return enableDrawing;
}
// to do see wtf is the addBugdet function and if not there do it