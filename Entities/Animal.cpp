#include <iostream>
#include "Animal.h"
#include "food.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include "../Core/GameObject.h"
using namespace std;

point Chick::chickDimensions = {50, 50};
point Cow::cowDimensions = {90, 60};
point Wolf::wolfDimensions = {80, 50};

Animal::Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
	curr_pos = r_point;
	curr_vel.x = 4;
	curr_vel.y = 4;

}

void Animal::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
	int remaining = getremainingfood();
	if (remaining > 0) {
		int boxWidth = 25;
		int boxHeight = 20;
		int boxX = RefPoint.x + (width / 2) - (boxWidth / 2);
		int boxY = RefPoint.y - boxHeight - 3;

		// Draw box background
		pWind->SetPen(BLACK, 1);
		pWind->SetBrush(LIGHTGRAY);
		pWind->DrawRectangle(boxX, boxY, boxX + boxWidth, boxY + boxHeight, FILLED);

		// Draw border
		pWind->SetPen(BLACK, 1);
		pWind->SetBrush(TRANSPARENT);
		pWind->DrawRectangle(boxX, boxY, boxX + boxWidth, boxY + boxHeight, FRAME);

		// Draw the number
		pWind->SetFont(14, BOLD, BY_NAME, "Arial");
		pWind->SetPen(BLACK, 1);
		pWind->DrawString(boxX + 8, boxY + 3, to_string(remaining));
	}
}

string Animal::getImagePath() const
{
	return image_path;
}

//// Timer for animals products
//void Animal::produce(int duration) {
//	if (chrono::steady_clock::now() >= end) {
//		end += chrono::seconds(duration);
//		// produce product
//		cout << "Animal produced a product!" << endl;
//	}
//}




// ####################++++++++++----------CHICK----------++++++++++####################

Chick::Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{
	for (int i = 0; i < 15; i++) {
		PrevCollwithFoodArea[i] = false;
		CurrCollwithFoodArea[i] = false;
	}
}

void Chick::velocity()
{
	static thread_local std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(7, 9);
	curr_vel.x = dist(gen);
	curr_vel.y = dist(gen);
}

int Chick::getChickSizeInX()
{
	return chickDimensions.x;
}

int Chick::getChickSizeInY()
{
	return chickDimensions.y;
}

void Chick::moveStep()
{
	window* pWind = pGame->getWind();
	curr_pos.x += curr_vel.x;
	curr_pos.y += curr_vel.y;
	RefPoint = curr_pos;
	pGame->getFarm()->keepInFarm(curr_pos, curr_vel, { chickDimensions.x, chickDimensions.y }, 9, 7);
	pWind->DrawImage(getImagePath(), curr_pos.x, curr_pos.y, width, height);
	draw();
}

void Chick::ifColl() {
	for (int i = 0; i < WaterIcon::waterAmount(); i++) {
		PrevCollwithFoodArea[i] = CurrCollwithFoodArea[i];
		if (WaterIcon::FoodAreaList[i] != nullptr) {
			FoodArea* FoodA = WaterIcon::FoodAreaList[i];
			point FoodAsize = { FoodA->getFoodAreaX(), FoodA->getFoodAreaY() };
			point FoodAref = FoodA->getFoodAreaRef();
			if (RefPoint.x >= FoodAref.x && RefPoint.x <= FoodAref.x + FoodAsize.x && RefPoint.y >= FoodAref.y && RefPoint.y <= FoodAref.y + FoodAsize.y) { CurrCollwithFoodArea[i] = true; }
			else if (RefPoint.x + chickDimensions.x >= FoodAref.x && RefPoint.x + chickDimensions.x <= FoodAref.x + FoodAsize.x && RefPoint.y >= FoodAref.y && RefPoint.y <= FoodAref.y + FoodAsize.y) { CurrCollwithFoodArea[i] = true; }
			else if (RefPoint.x >= FoodAref.x && RefPoint.x <= FoodAref.x + FoodAsize.x && RefPoint.y + chickDimensions.y >= FoodAref.y && RefPoint.y + chickDimensions.y <= FoodAref.y + FoodAsize.y) { CurrCollwithFoodArea[i] = true; }
			else if (RefPoint.x + chickDimensions.x >= FoodAref.x && RefPoint.x + chickDimensions.x <= FoodAref.x + FoodAsize.x && RefPoint.y + chickDimensions.y >= FoodAref.y && RefPoint.y + chickDimensions.y <= FoodAref.y + FoodAsize.y) { current_coll = true; }
			else { CurrCollwithFoodArea[i] = false; }
			if (CurrCollwithFoodArea[i] == true && PrevCollwithFoodArea[i] == false) {
				FoodA->decreaseFood(1);
				foodeaten += 1;
			}
		}
	}
};

bool Chick::getPrevColl() const
{
	return prev_coll;
}

bool Chick::getCurrColl() const
{
	return current_coll;
}

void Chick::setColl(bool prev, bool curr)
{
	prev_coll = prev;
	current_coll = curr;
}

int Chick::getFoodeaten()
{
	return foodeaten;
}

void Chick::setFoodeaten(int value)
{
	foodeaten = value;
}

void Chick::Resetfoodeaten()
{
	foodeaten = 0;
}

int Chick::getremainingfood() const {
	int needed = 2;
	if (this->foodeaten == 0) return needed;
	return needed - this->foodeaten;
}

bool Chick::preyed(Wolf* W) {
	if (!W) return false;
	return (RefPoint.x + chickDimensions.x >= W->getRefPointX()
		&& RefPoint.x <= W->getRefPointX() + W->getWolfSizeInX()
		&& RefPoint.y + chickDimensions.y >= W->getRefPointY()
		&& RefPoint.y <= W->getRefPointY() + W->getWolfSizeInY());
}




// ####################++++++++++----------COW----------++++++++++####################

Cow::Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{
	for (int i = 0; i < 15; i++) {
		PrevCollwithFoodArea[i] = false;
		CurrCollwithFoodArea[i] = false;
	}
}

void Cow::velocity()
{
	static thread_local std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(3,4);
	curr_vel.x = dist(gen);
	curr_vel.y = dist(gen);
}

int Cow::getCowSizeInX()
{
	return cowDimensions.x;
}

int Cow::getCowSizeInY()
{
	return cowDimensions.y;
}

void Cow::moveStep()
{
	window* pWind = pGame->getWind();
	curr_pos.x += curr_vel.x;
	curr_pos.y += curr_vel.y;
	RefPoint = curr_pos;
	pGame->getFarm()->keepInFarm(curr_pos, curr_vel, { cowDimensions.x, cowDimensions.y }, 4, 3);
	pWind->DrawImage(getImagePath(), curr_pos.x, curr_pos.y, width, height);
	draw();

}

void Cow::ifColl() {
	for (int i = 0; i < WaterIcon::waterAmount(); i++) {
		PrevCollwithFoodArea[i] = CurrCollwithFoodArea[i];
		if (WaterIcon::FoodAreaList[i] != nullptr) {
			FoodArea* FoodA = WaterIcon::FoodAreaList[i];
			point FoodAsize = { FoodA->getFoodAreaX(), FoodA->getFoodAreaY() };
			point FoodAref = FoodA->getFoodAreaRef();
			if (RefPoint.x >= FoodAref.x && RefPoint.x <= FoodAref.x + FoodAsize.x && RefPoint.y >= FoodAref.y && RefPoint.y <= FoodAref.y + FoodAsize.y) { CurrCollwithFoodArea[i] = true; }
			else if (RefPoint.x + cowDimensions.x >= FoodAref.x && RefPoint.x + cowDimensions.x <= FoodAref.x + FoodAsize.x && RefPoint.y >= FoodAref.y && RefPoint.y <= FoodAref.y + FoodAsize.y) { CurrCollwithFoodArea[i] = true; }
			else if (RefPoint.x >= FoodAref.x && RefPoint.x <= FoodAref.x + FoodAsize.x && RefPoint.y + cowDimensions.y >= FoodAref.y && RefPoint.y + cowDimensions.y <= FoodAref.y + FoodAsize.y) { CurrCollwithFoodArea[i] = true; }
			else if (RefPoint.x + cowDimensions.x >= FoodAref.x && RefPoint.x + cowDimensions.x <= FoodAref.x + FoodAsize.x && RefPoint.y + cowDimensions.y >= FoodAref.y && RefPoint.y + cowDimensions.y <= FoodAref.y + FoodAsize.y) { CurrCollwithFoodArea[i] = true; }
			else { CurrCollwithFoodArea[i] = false; }
			if (CurrCollwithFoodArea[i] == true && PrevCollwithFoodArea[i] == false) {
				FoodA->decreaseFood(1);
				foodeaten += 1;
			}
		}
	}
}

bool Cow::getPrevColl() const
{
	return prev_coll;
}

bool Cow::getCurrColl() const
{
	return current_coll;
}

void Cow::setColl(bool prev, bool curr)
{
	prev_coll = prev;
	current_coll = curr;
}

int Cow::getFoodeaten()
{
	return foodeaten;
}

void Cow::setFoodeaten(int value)
{
	foodeaten = value;
}

void Cow::Resetfoodeaten()
{
	foodeaten = 0;
}

int Cow::getremainingfood() const {
	int needed = 4;
	if (this->foodeaten == 0) return needed;
	return needed - this->foodeaten;
}

bool Cow::preyed(Wolf* W) {
	if (!W) return false;
	return (RefPoint.x + cowDimensions.x >= W->getRefPointX()
		&& RefPoint.x <= W->getRefPointX() + W->getWolfSizeInX()
		&& RefPoint.y + cowDimensions.y >= W->getRefPointY()
		&& RefPoint.y <= W->getRefPointY() + W->getWolfSizeInY());
}



// ####################++++++++++----------WOLF----------++++++++++####################

Wolf::Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: Animal(r_pGame, r_point, r_width, r_height, img_path)
{
	cout << "wolf constructor" << endl;
}

void Wolf::velocity()
{
	static thread_local std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(4, 6);
	curr_vel.x = dist(gen);
	curr_vel.y = dist(gen);
}

int Wolf::getWolfSizeInX()
{
	return wolfDimensions.x;
}

int Wolf::getWolfSizeInY()
{
	return wolfDimensions.y;
}

int Wolf::getRefPointX() const
{
	return RefPoint.x;
}

int Wolf::getRefPointY() const
{
	return RefPoint.y;
}

void Wolf::moveStep()
{
	window* pWind = pGame->getWind();
	curr_pos.x += curr_vel.x;
	curr_pos.y += curr_vel.y;
	RefPoint = curr_pos;
	pGame->getFarm()->keepInFarm(curr_pos, curr_vel, { wolfDimensions.x, wolfDimensions.y }, 6, 4);
	pWind->DrawImage(getImagePath(), curr_pos.x, curr_pos.y, width, height);
}

int Wolf::getremainingfood() const {
	return -1;
}

bool Wolf::slayed(int x, int y) {
	if (x >= RefPoint.x && x <= RefPoint.x + wolfDimensions.x && y >= RefPoint.y && y <= RefPoint.y + wolfDimensions.y) {
		cout << "Wolf clicked!" << endl;
		if (!--clicks) {
			cout << "Wolf removed!" << endl;
			return true;
		}
	}
	return false;
}