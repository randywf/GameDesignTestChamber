#include "GameClock.h"
#include <iostream>
#include <iomanip>

// Define speed of game
const int TICKRATE = 5;
const int SKIP_TICKS = 1000000000 / TICKRATE;

// Loop section
int main(void)
{
	GameClock gametime;
	timespec current, previous;
	timespec sleep_curr, sleep_prev;
	int elapsed_ns, elapsed_s, ticks_per_sec, accumulated;

	std::cout << "Beginning game loop..." << std::endl;
	std::cout << "Start time: ";
	std::cout << gametime.GetStartTime().tv_sec << "." << gametime.GetStartTime().tv_nsec << " seconds" << std::endl;

	previous = gametime.GetCurrentTime();
	accumulated = 0;

	while(1)
	{
		current = gametime.GetCurrentTime();

		// Calculate elapsed time
		// This is used to double check that the tickrate is correct
		if (current.tv_sec == previous.tv_sec) {
			elapsed_ns = current.tv_nsec - previous.tv_nsec;
		}
		else {
			elapsed_s = current.tv_sec - previous.tv_sec;
			elapsed_ns = current.tv_nsec + (elapsed_s * 1000000000) - previous.tv_nsec;
		}

		// Find TPS
		ticks_per_sec = 1000000000 / elapsed_ns;

		// sleep until one time step has passed
		while (accumulated < SKIP_TICKS)
		{
			sleep_curr = gametime.GetCurrentTime();
			if (sleep_curr.tv_nsec > sleep_prev.tv_nsec) {
				accumulated += sleep_curr.tv_nsec - sleep_prev.tv_nsec;
			}
			else {
				accumulated += sleep_curr.tv_nsec + 1000000000 - sleep_prev.tv_nsec;
			}
			sleep_prev = sleep_curr;
		}
		while (accumulated >= SKIP_TICKS)
		{
			accumulated -= SKIP_TICKS;
		}

		std::cout << "Ticks per second:" << ticks_per_sec << std::endl;
		
		previous = current;
	}
}