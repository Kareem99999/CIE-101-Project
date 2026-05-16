#pragma once
#include <chrono>
#include "../Core/Drawable.h"

class Animal :public Drawable
{
private:
	string image_path;
	int foodeaten = 0;
	// Timer variables for animals products
public:
	point curr_pos;
	point curr_vel;
	Animal(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	string getImagePath() const;
	virtual void draw() const override;
	virtual void velocity() = 0;
	virtual void moveStep() = 0;
	virtual int getremainingfood() const  = 0;
	//void produce(int duration);
};

// Forward declaration so classes can reference Wolf* before Wolf is defined
class Wolf;

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
	virtual void moveStep();
	void ifColl();
	bool getPrevColl() const;
	bool getCurrColl() const;
	void setColl(bool prev, bool curr);
	int getFoodeaten();
	void setFoodeaten(int value);
	void Resetfoodeaten();
	int getremainingfood() const override;
	bool preyed(Wolf* W);
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
	bool preyed(Wolf* W);
	virtual void velocity();
	int static getCowSizeInX();
	int static getCowSizeInY();
	virtual void moveStep();
	void ifColl();
	bool getPrevColl() const;
	bool getCurrColl() const;
	void setColl(bool prev, bool curr);
	int getFoodeaten();
	void setFoodeaten(int value);
	void Resetfoodeaten();
	int getremainingfood() const override;
	bool* PrevCollwithFoodArea = new bool[15];
	bool* CurrCollwithFoodArea = new bool[15];
};

class Wolf : public Animal
{
private:
	point static wolfDimensions;
	int clicks = 5;
public:
	Wolf(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	void velocity() override;
	int static getWolfSizeInX();
	int static getWolfSizeInY();
	int getRefPointX() const;
	int getRefPointY() const;
	void moveStep() override;
	int getremainingfood() const override;
	bool slayed(int, int);
};

