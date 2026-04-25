#pragma once
using TIMER = std::chrono::steady_clock;
using TIME = TIMER::time_point;

class Timer {
private:
	TIME start = TIME::min();
	TIME end = TIME::min();
public:
	Timer(int);
	void setDuration(int duration);
	bool check() const;
	long long elapsed() const;
	void reset();
	long long remaining() const;
};