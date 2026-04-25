#include <iostream>
#include <chrono>
#include "..\Core\Timer.h"

Timer::Timer(int duration = 60) {
	start = TIMER::now();
	end = start + std::chrono::seconds(duration);
}

long long Timer::setDuration(int duration) {
	end = start + std::chrono::seconds(duration);
}

bool Timer::check() const {
	if (TIMER::now() >= end) {
		return true;
	}
	return false;
}

long long Timer::elapsed() const {
	return std::chrono::duration_cast<std::chrono::seconds>(TIMER::now() - start).count();
	// trunckate to seconds
}

void Timer::reset() const {
	start = TIMER::now();
}