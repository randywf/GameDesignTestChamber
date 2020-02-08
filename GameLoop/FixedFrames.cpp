#include "GameClock.h"
#include <iostream>

// Define speed of game
const int FRAMES_PER_SECOND = 1;
const int SKIP_TICKS = 1000000000 / FRAMES_PER_SECOND;

// Loop section
int main(void)
{
	GameClock game_clock;
	struct timespec game_time = game_clock.GetStartTime();
	unsigned long long int current_game_tick = (game_time.tv_sec * 1000000000) + game_time.tv_nsec;
	unsigned long long int next_game_tick = current_game_tick + SKIP_TICKS;
	unsigned int nanoseconds_to_sleep = 0;
	int current_frame = 0;
	std::cout << game_time.tv_sec << " + " << game_time.tv_nsec << std::endl;
	std::cout << current_game_tick << std::endl;
	std::cout << next_game_tick << std::endl;
	
	while(1) {
		current_frame++;
		std::cout << current_frame << std::endl;
		game_time = game_clock.GetCurrentTime();
		current_game_tick = (game_time.tv_sec * 1000000000) + game_time.tv_nsec;
		next_game_tick = current_game_tick + SKIP_TICKS;
		nanoseconds_to_sleep = next_game_tick;
		std::cout << nanoseconds_to_sleep << std::endl;
		game_clock.SleepFor(nanoseconds_to_sleep);
	}
}