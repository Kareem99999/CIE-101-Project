#include <iostream>
#include <thread>
#include <chrono>
#include "..\Core\Timer.h"

TIME Timer::delay = TIMER::now();
Timer::Timer(int duration = 60) {
	start = TIMER::now();
	end = start + std::chrono::milliseconds(duration);
}

void Timer::setDuration(int Duration = 60) {
	start = TIMER::now();
	end = start + std::chrono::milliseconds(Duration);
}

bool Timer::check() const {
	if (TIMER::now() >= end) {
		return true;
	}
	return false;
}

//bool Timer::delayed(int duration) const {
//	delay = TIMER::now() + std::chrono::milliseconds(duration);
//	if (TIMER::now() >= delay) {
//		return true;
//	}
//	return false;
//}

long long Timer::elapsed() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(TIMER::now() - start).count();
	// trunckate to seconds
}

long long Timer::remaining() const {
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - TIMER::now()).count();
	// trunckate to seconds
}
