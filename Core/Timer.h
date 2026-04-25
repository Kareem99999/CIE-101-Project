#pragma once
#include <chrono>
using TIMER = std::chrono::steady_clock;
using TIME = TIMER::time_point;

class Timer {
private:
	TIME start = TIME();
	TIME end = TIME();
	static TIME delay;
public:
	Timer(int duration);
	void setDuration(int Duration);
	bool check() const;
	//bool delayed(int duration) const;
	long long elapsed() const;
	long long remaining() const;
};