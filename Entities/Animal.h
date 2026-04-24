#pragma once
#include "../Core/Drawable.h"

class Animal :public Drawable
{
private:
	string image_path;
public:
	point curr_pos;
	point curr_vel;
	Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	string getImagePath() const;
	virtual void draw() const override;
	virtual void velocity() = 0;
	virtual void moveStep() = 0;
};

class Chick : public Animal
{
private:
	point static chickDimensions;
public:
	Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void velocity();
	int static getChickSizeInX();
	int static getChickSizeInY();
	virtual void moveStep();
};

class Cow : public Animal
{
private:
	point static cowDimensions;
public:
	Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void velocity();
	int static getCowSizeInX();
	int static getCowSizeInY();
	virtual void moveStep();
};

