#include "pch.h"
#include "Timer.h"
#include "World.h"


Timer::Timer() : active(false)
{
	onTick = []() {};
	onFinished = []() {};

	world.timers.push_back(this);
}

Timer::Timer(const Timer& other)
{
}

Timer::~Timer()
{
	world.timers.erase(remove(world.timers.begin(), world.timers.end(), this), world.timers.end());
}

void Timer::update(float dt)
{
	if (!active) return;

	duration.first += dt;
	if (duration.first > duration.second){
		onTick();
		duration.first = 0;
		if (++count.first >= count.second) {
			active = false;
			onFinished();
		}
	}
}

void Timer::start()
{
	active = true;
}

void Timer::stop()
{
	active = false;
}

void Timer::reset(float duration, int count, bool autoStart)
{
	active = autoStart;
	this->duration = pair<float, float>(0.0f, duration);
	this->count = pair<int, int>(0, count);
}