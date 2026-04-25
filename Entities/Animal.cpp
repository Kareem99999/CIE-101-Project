#include "Animal.h"
#include "../Config/GameConfig.h"
#include "../Core/Game.h"
#include "../Core/GameObject.h"
#include <iostream>
using namespace std;

point Chick::chickDimensions = { 50,50 };
point Cow::cowDimensions = { 90,60 };

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
}

string Animal::getImagePath() const
{
	return image_path;
}

void Chick::isCollCh()
{
	prevColl = currColl;
	if (curr_pos.x < (config.windWidth / 2) + 50 && curr_pos.x > config.windWidth / 2 && curr_pos.y < (config.windHeight / 2) + 50 && curr_pos.y > config.windHeight / 2 ) {
		currColl = true;
		cout << "A collision occured \n";
	}
	else if (curr_pos.x + 50 < (config.windWidth / 2) + 50 && curr_pos.x + 50 > config.windWidth / 2 && curr_pos.y + 50 < (config.windHeight / 2) + 50 && curr_pos.y + 50 > config.windHeight / 2 ) {
		currColl = true;
		cout << "A collision occured \n";
	}
	else { 
		currColl = false; 
	}
}

void Cow::isCollCo()
{
	prevColl = currColl;
	if (curr_pos.x < (config.windWidth / 2) + 50 && curr_pos.x > config.windWidth / 2 && curr_pos.y < (config.windHeight / 2) + 50 && curr_pos.y > config.windHeight / 2) {
		currColl = true;
		cout << "A collision occured \n";
	}
	else if (curr_pos.x + 90 < (config.windWidth / 2) + 50 && curr_pos.x + 90 > config.windWidth / 2 && curr_pos.y + 60 < (config.windHeight / 2) + 50 && curr_pos.y + 60 > config.windHeight / 2) {
		currColl = true;
		cout << "A collision occured \n";
	}
	else {
		currColl = false;
	}
}

int Animal::TakeFood()
{
	if (currColl == true && prevColl == false) {
		return 1;
	}
	else {
		return 0;
	}
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
