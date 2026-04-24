#pragma once
#include "../Core/Drawable.h"
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
	void static  increaseAnimals();
	void static setRangeMinX(int valueMinX);
	void static setRangeMaxX(int valueMaxX);
	void static setRangeMinY(int valueMinY);
	void static setRangeMaxY(int valueMaxY);
};

class ChickIcon : public BudgetbarIcon
{
public:
	static Chick** chickList; //an array of Chick pointers
	static int count;
	ChickIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();
};

class CowIcon : public BudgetbarIcon
{
public:	
	static Cow** cowList;
	static int count;
	CowIcon::CowIcon(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void onClick();
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

	ANIMAL_COUNT		//no. of menu icons ==> This should be the last line in this enum
};

class Budgetbar : public Drawable
{
private:
	BudgetbarIcon** iconsList; //an array of toolbarIcon pointers
	string iconsImages[ANIMAL_COUNT];

public:
	Budgetbar(Game* r_pGame, point r_point, int r_width, int r_height);
	~Budgetbar();
	void draw() const override;
	bool handleClick(int x, int y);	//handles clicks on toolbar icons, returns true if exit is clicked

};

