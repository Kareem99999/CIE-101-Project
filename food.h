#pragma once
#include "../Core/Drawable.h"
#include<string>
using namespace std;
class food : public Drawable
{
protected: 
	int amount;
	int sellprice;
	int buyprice;
	string name;
	string foodImagePath;
public:
	food(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override;
	virtual void addFood(int amount) = 0;
	virtual void buy() = 0;
	virtual void sell() = 0;
};
/*class grass : public food {
public:
	grass(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	void draw() const override;
	void buy();
	void sell();
	void addFood(int amount);
};
*/
class eggs : public food {
public:
	eggs(Game* r_pGame, point r_point, int r_width, int r_height);
	void draw() const override;
	void addFood(int amount);
	void buy();
	void sell();
};
class milk : public food {
public:
	milk(Game* r_pGame, point r_point, int r_width, int r_height);
	void draw() const override;
	void buy();
	void sell();
	void addFood(int amount);

};