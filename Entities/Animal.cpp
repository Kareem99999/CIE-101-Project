#include "Animal.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include "../Core/GameObject.h"
#include <iostream>
using namespace std;

point Chick::chickDimensions = { 50,50 };
point Cow::cowDimensions = { 90,60 };
point Wolf::wolfDimensions = { 80,50 };

Animal::Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Drawable(r_pGame, r_point, r_width, r_height)
{
	image_path = img_path;
	curr_pos = r_point;
	curr_vel.x = 4;
	curr_vel.y = 4;

}

int Chick::ifColl() {
	this->prev_coll = this->current_coll;
	FoodArea* FoodA = pGame->getFoodArea();
	point FoodAsize = FoodA->getFoodAreaDim();
	point FoodAref = FoodA->getFoodAreaRef();
	if (RefPoint.x >= FoodAref.x && RefPoint.x <= FoodAref.x + FoodAsize.x && RefPoint.y >= FoodAref.y && RefPoint.y <= FoodAref.y + FoodAsize.y) { current_coll = true; }
	else if (RefPoint.x + chickDimensions.x >= FoodAref.x && RefPoint.x + chickDimensions.x <= FoodAref.x + FoodAsize.x && RefPoint.y >= FoodAref.y && RefPoint.y <= FoodAref.y + FoodAsize.y) { current_coll = true; }
	else if (RefPoint.x >= FoodAref.x && RefPoint.x <= FoodAref.x + FoodAsize.x && RefPoint.y + chickDimensions.y >= FoodAref.y && RefPoint.y + chickDimensions.y <= FoodAref.y + FoodAsize.y) { current_coll = true; }
	else if (RefPoint.x + chickDimensions.x >= FoodAref.x && RefPoint.x + chickDimensions.x <= FoodAref.x + FoodAsize.x && RefPoint.y + chickDimensions.y >= FoodAref.y && RefPoint.y + chickDimensions.y <= FoodAref.y + FoodAsize.y) { current_coll = true; }
	else {	current_coll = false;	}
	if (FoodA != nullptr) {
		if (current_coll == true && prev_coll == false) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else return 0;
};


int Cow::ifColl() {
	prev_coll = current_coll;
	FoodArea* FoodA = pGame->getFoodArea();
	point FoodAsize = FoodA->getFoodAreaDim();
	point FoodAref = FoodA->getFoodAreaRef();
	if (RefPoint.x >= FoodAref.x && RefPoint.x <= FoodAref.x + FoodAsize.x && RefPoint.y >= FoodAref.y && RefPoint.y <= FoodAref.y + FoodAsize.y) { current_coll = true; }
	else if (RefPoint.x + cowDimensions.x >= FoodAref.x && RefPoint.x + cowDimensions.x <= FoodAref.x + FoodAsize.x && RefPoint.y >= FoodAref.y && RefPoint.y <= FoodAref.y + FoodAsize.y) { current_coll = true; }
	else if (RefPoint.x >= FoodAref.x && RefPoint.x <= FoodAref.x + FoodAsize.x && RefPoint.y + cowDimensions.y >= FoodAref.y && RefPoint.y + cowDimensions.y <= FoodAref.y + FoodAsize.y) { current_coll = true; }
	else if (RefPoint.x + cowDimensions.x >= FoodAref.x && RefPoint.x + cowDimensions.x <= FoodAref.x + FoodAsize.x && RefPoint.y + cowDimensions.y >= FoodAref.y && RefPoint.y + cowDimensions.y <= FoodAref.y + FoodAsize.y) { current_coll = true; }
	else {
		current_coll = false;
	}
	if (FoodA != nullptr) {
		if (current_coll == true && prev_coll == false) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else return 0;
};


void Animal::draw() const
{
	//draw image of this object
	window* pWind = pGame->getWind();
	pWind->DrawImage(image_path, RefPoint.x, RefPoint.y, width, height);
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

Chick::Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{}

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
	RefPoint.x += curr_vel.x;
	RefPoint.y += curr_vel.y;
	pGame->getFarm()->keepInFarm(RefPoint, curr_vel, { chickDimensions.x, chickDimensions.y }, 9, 7);
	pWind->DrawImage(getImagePath(), RefPoint.x, RefPoint.y, width, height);
}

Cow::Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path) : Animal(r_pGame, r_point, r_width, r_height, img_path)
{}

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
	RefPoint.x += curr_vel.x;
	RefPoint.y += curr_vel.y;
	pGame->getFarm()->keepInFarm(RefPoint, curr_vel, { cowDimensions.x, cowDimensions.y }, 4, 3);
	pWind->DrawImage(getImagePath(), RefPoint.x, RefPoint.y, width, height);

}

Wolf::Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
	: Animal(r_pGame, r_point, r_width, r_height, img_path)
{}

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

void Wolf::moveStep()
{
	window* pWind = pGame->getWind();
	RefPoint.x += curr_vel.x;
	RefPoint.y += curr_vel.y;
	pGame->getFarm()->keepInFarm(RefPoint, curr_vel, { wolfDimensions.x, wolfDimensions.y }, 6, 4);
	pWind->DrawImage(getImagePath(), RefPoint.x, RefPoint.y, width, height);
}
