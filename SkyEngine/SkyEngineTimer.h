#pragma once
#include <chrono>

class SkyTimer
{
public:
	SkyTimer();
	float Mark();
	float Peek() const;
private:
	std::chrono::steady_clock::time_point last;
};
