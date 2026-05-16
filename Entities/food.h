#pragma once
#include "../Core/Drawable.h"
#include <string>
#include <chrono>

using namespace std;
using TIMER = std::chrono::steady_clock;
using TIME = TIMER::time_point;
class Durations {
private:
	TIME start = TIME();
	TIME end = TIME();
public:
	Durations(int duration);
	void setDuration(int Duration);
	bool checkEnd() const;
	double remainingInSeconds() const;
};

class food : public Drawable
{
protected: 
	int amount;
	static int sellprice;
	string foodImagePath;
	bool enableDrawing = true;
public:

	Durations* appearingTimer;
	food(Game* r_pGame, point r_point, int r_width, int r_height, string img_path);
	virtual void draw() const override = 0;
	virtual void onClick(int posX, int posY) = 0;
	virtual bool isEnableDrawing() const = 0;
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
	bool virtual isEnableDrawing() const override;
	static int getsellPrice();
};
class milk : public food {
public:
	//Timer* appearingTimer;
	milk(Game* r_pGame, point r_point, int r_width, int r_height);
	void draw() const override;
	void onClick(int posX, int posY) override;
	static int getsellPrice();
	void Saving(ofstream& saveFile) const;
	void LoadEnability(bool enable);
	bool virtual isEnableDrawing() const override;
	void addFood(int amount) override;

};