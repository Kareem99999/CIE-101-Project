#pragma once
#include "../Core/Drawable.h"
#include<string>
using namespace std;
class food : public Drawable
{
protected: 
	int amount;
	static int sellprice;
	string name;
	string foodImagePath;
	bool enableDrawing = true;
public:
	food(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override = 0;
	virtual void onClick(int posX, int posY) = 0;
	virtual void addFood(int amount) = 0;
};

class eggs : public food {
public:
	eggs(Game* r_pGame, point r_point, int r_width, int r_height);
	void draw() const override;
	void onClick(int posX, int posY) override;
	void addFood(int amount) override;
	void Saving(ofstream& saveFile) const;
	void LoadEnability(bool enable);
	static int getsellPrice();
};
class milk : public food {
public:
	milk(Game* r_pGame, point r_point, int r_width, int r_height);
	void draw() const override;
	void onClick(int posX, int posY) override;
	static int getsellPrice();
	void Saving(ofstream& saveFile) const;
	void LoadEnability(bool enable);
	void addFood(int amount) override;

};