#pragma once
#include <chrono>
#include "../Core/Drawable.h"

class Animal :public Drawable
{
private:
	string image_path;
	// Timer variables for animals products
public:
	point curr_pos;
	point curr_vel;
	Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	string getImagePath() const;
	virtual void draw() const override;
	virtual void velocity() = 0;
	virtual void moveStep() = 0;
	//void produce(int duration);
};

class Chick : public Animal
{
private:
	point static chickDimensions;
	bool prev_coll = false;
	bool current_coll = false;
	int foodeaten = 0;
public:
	Chick(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void velocity();
	int static getChickSizeInX();
	int static getChickSizeInY();
	void ifColl();
	int getFoodeaten();
	virtual void moveStep();
	bool* PrevCollwithFoodArea = new bool[15];
	bool* CurrCollwithFoodArea = new bool[15];
};

class Cow : public Animal
{
private:
	point static cowDimensions;
	bool prev_coll = false;
	bool current_coll = false;
	int foodeaten = 0;
public:
	Cow(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void velocity();
	int static getCowSizeInX();
	int static getCowSizeInY();
	virtual void moveStep();
	int getFoodeaten();
	void ifColl();
	bool* PrevCollwithFoodArea = new bool[15];
	bool* CurrCollwithFoodArea = new bool[15];
};

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
