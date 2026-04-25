#include "../Entities/Wolf.h"

// No more cute animals.. BEHOLD THE MIGHTY WOLF!!

Wolf::Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path)
: Animal(r_pGame, r_point, r_width, r_height, "images\\wolf.png")
{
}

void Wolf::draw() const
{
	window* pWind = pGame->getWind();
	pWind->DrawImage(getImagePath(), RefPoint.x, RefPoint.y, width, height);
}


void Wolf::velocity()
{
	static thread_local std::mt19937 gen{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(3, 4);
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
	pGame->getFarm()->keepInFarm(RefPoint, curr_vel, { wolfDimensions.x, wolfDimensions.y }, 4, 3);
	pWind->DrawImage(getImagePath(), RefPoint.x, RefPoint.y, width, height);
}
