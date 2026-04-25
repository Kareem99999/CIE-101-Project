#pragma once
#include "../Entities/Animal.h"

// No more cute animals.. BEHOLD THE MIGHTY WOLF!!

class Wolf : public Animal
{
private:
	point static wolfDimensions;
public:
	Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void velocity();
	int static getWolfSizeInX();
	int static getWolfSizeInY();
	virtual void moveStep();
};
