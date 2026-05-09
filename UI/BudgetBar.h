#pragma once
#include "../Core/Drawable.h"
#include "../Core/Gameobject.h"
#include "../Entities/Animal.h"
#include "../Config/GameConfig.h"
#include <random>
#include <limits>

//Base class for all toolbar icons 
class BudgetbarIcon :public Drawable
{
protected:
	//string image_path;
	static int range_min_x;
	static int range_max_x;
	static int range_min_y;
	static int range_max_y;
	int static AnimalsCounter;
public:
	string image_path;
	BudgetbarIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override;
	virtual void onClick() = 0;   //The action that should be taken when this icon is clicked
	int static  getAnimalCounter();
	void static setAnimalCounter(int value);
	void static increaseAnimals();
	int static  getRangeMinX();
	int static getRangeMaxX();
	int static getRangeMinY();
	int static getRangeMaxY();
	void static setRangeMinX(int valueMinX);
	void static setRangeMaxX(int valueMaxX);
	void static setRangeMinY(int valueMinY);
	void static setRangeMaxY(int valueMaxY);
	virtual void Saving(ofstream& saveFile) const = 0;
	virtual void Loading(ifstream& loadFile) const = 0;
};

class ChickIcon : public BudgetbarIcon
{
public:
	static Chick** chickList; //an array of Chick pointers
	static int count;
	ChickIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();
	virtual void Saving(ofstream& saveFile) const;
	virtual void Loading(ifstream& loadFile) const;
};

class CowIcon : public BudgetbarIcon
{
public:	
	static Cow** cowList;
	static int count;
	CowIcon::CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();
	virtual void Saving(ofstream& saveFile) const;
	virtual void Loading(ifstream& loadFile) const;
};

// TO DO: The rest of icons in the toolbar

enum ANIMAL_ICONS //The icons of the toolbar (you should add more icons)
{
	//Note: Icons are ordered here as they appear in menu
	//If you want to change the menu icons order, change the order here
	ICON_CHICK,

	//TODO: Add more icons names here
	//Cow icon
	ICON_COW,

	ICON_WATER,

	BUDGET_ICON_COUNT		//no. of menu icons ==> This should be the last line in this enum
};

class Budgetbar : public Drawable
{
private:
	BudgetbarIcon** iconsList; //an array of toolbarIcon pointers
	string iconsImages[BUDGET_ICON_COUNT];

public:
	Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height);
	~Budgetbar();
	void draw() const override;
	BudgetbarIcon* getIcon(int iconIndex) const;
	bool handleClick(int x, int y);	//handles clicks on toolbar icons, returns true if exit is clicked

};

class WaterIcon : public BudgetbarIcon
{
public:
	int static amount;
	WaterIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	static FoodArea** FoodAreaList;
	virtual void onClick();
	int static waterAmount();
	void decreaseWater();
	virtual void Saving(ofstream& saveFile) const;
	virtual void Loading(ifstream& loadFile) const;
};