#include "GameClock.h"
#include <ctime>

GameClock::GameClock()
{
	clock_gettime(CLOCK_MONOTONIC, &this->start_time);
	return;
}

struct timespec GameClock::GetStartTime()
{
	return this->start_time;
}

struct timespec GameClock::GetCurrentTime()
{
	clock_gettime(CLOCK_MONOTONIC, &this->current_time);
	return this->current_time;
}

struct timespec GameClock::GetElapsedTime()
{
	clock_gettime(CLOCK_MONOTONIC, &this->current_time);
	elapsed_time.tv_sec = current_time.tv_sec - start_time.tv_sec;
	elapsed_time.tv_nsec = current_time.tv_nsec - start_time.tv_nsec;
	if (elapsed_time.tv_nsec < 0) {
		elapsed_time.tv_sec--;
		elapsed_time.tv_nsec = 999999999 + elapsed_time.tv_nsec;
	}
	return elapsed_time;
}

void GameClock::SleepFor(unsigned int nanoseconds)
{
	struct timespec target_time = this->GetCurrentTime();
	target_time.tv_nsec = target_time.tv_nsec + nanoseconds % 1000000000;
	target_time.tv_sec = target_time.tv_sec + nanoseconds / 1000000000;
	return;
}