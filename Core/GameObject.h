#pragma once
#include "Drawable.h"

class GameObject : public Drawable
{
protected:
	static color fillColor;	//game object fill color
	static color borderColor;	//game object border color

public:
	GameObject(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc);
	virtual void draw() const = 0; //for a game object to draw itself on the screen
	void setRefPoint(point p);
	bool CollisionDetection(const GameObject& gObj);

	//-- The following functions should be supported by the shape class
	//-- It should be overridden by each inherited shape
	//-- Decide the parameters that you should pass to each function	

	//virtual void move() = 0;		//Move the game object
	//virtual void save(ofstream &OutFile) = 0;	//Save the shape parameters to the file
	//virtual void load(ifstream &Infile) = 0;	//Load the shape parameters to the file
	//virtual void collisionAction() = 0;    //action that should be performed upon collision

};

class Farm : public GameObject {
protected:
	int static FarmWidth;
	int static FarmHeight;
	static int margin;
public:
	Farm(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc);
	void draw() const override;
	int static getFarmWidth();
	int static getFarmHeight();
	static int getMargin();
	void keepInFarm(point& position, point& velocity, point dimensions, int maxVelo, int minVelo);
};

class Warehouse : public GameObject {
protected:
	int WarehouseWidth = 0;
	int WarehouseHeight = 0;
public:
	Warehouse(Game * r_pGame, point ref, int r_width, int r_height, color fc, color bc);
	void draw() const override;
};

class FoodArea : public GameObject {
protected:
	int FoodAreaWidth = 0;
	int FoodAreaHeight = 0;
public:
	FoodArea(Game* r_pGame, point ref, int r_width, int r_height, color fc, color bc);
	void draw() const override;
	void setFoodAreadim(int width, int height) { FoodAreaWidth = width, FoodAreaHeight = height }

};