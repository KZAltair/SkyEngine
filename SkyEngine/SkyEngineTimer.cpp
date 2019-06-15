#include "SkyEngineTimer.h"

using namespace std::chrono;

SkyTimer::SkyTimer()
{
	last = steady_clock::now();
}

float SkyTimer::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float>frameTime = last - old;
	return frameTime.count();
}

float SkyTimer::Peek() const
{
	return duration<float>(steady_clock::now() - last).count();
}
