#include <ctime>
#include <iomanip>
#include <iostream>

// Define tick rate of main loop
const int TICKRATE = 5;
const int SKIP_TICKS = 1000000000 / TICKRATE;

int main(void)
{
	timespec current, previous; // time at start and end of main loop
	timespec sleep_i, sleep_f; // time at start and end of sleep loop
	int elapsed_ns, elapsed_s, ticks_per_sec, accumulator;
	short first_loop = 1;

	clock_gettime(CLOCK_MONOTONIC, &previous);
	clock_gettime(CLOCK_MONOTONIC, &sleep_f);
	accumulator = 0;

	while(1) {
		clock_gettime(CLOCK_MONOTONIC, &current);

		if (first_loop != 1) {
			// Calculate elapsed time
			// This is used to double check that the tickrate is correct
			// Don't run on first iteration of loop (there's no previous time)
			if (current.tv_sec == previous.tv_sec) {
				elapsed_ns = current.tv_nsec - previous.tv_nsec;
			}
			else {
				elapsed_s = current.tv_sec - previous.tv_sec;
				elapsed_ns = current.tv_nsec + (elapsed_s * 1000000000) - previous.tv_nsec;
			}
			// Find ticks per second
			ticks_per_sec = 1000000000 / elapsed_ns;
			std::cout << "Elapsed nanosecs:" << elapsed_ns << std::endl;
			std::cout << "Ticks per second:" << ticks_per_sec << std::endl << std::endl;
		}
		else {
			first_loop = 0;
		}

		while (accumulator < SKIP_TICKS) {
			// sleep until one time step has passed
			clock_gettime(CLOCK_MONOTONIC, &sleep_i);
			if (sleep_i.tv_sec == sleep_f.tv_sec) {
				accumulator += sleep_i.tv_nsec - sleep_f.tv_nsec;
			}
			else {
				accumulator += sleep_i.tv_nsec + (sleep_i.tv_sec - sleep_f.tv_sec) * 1000000000 - sleep_f.tv_nsec;
			}
			sleep_f = sleep_i;
		}
		while (accumulator >= SKIP_TICKS) {
			accumulator -= SKIP_TICKS;
		}

		previous = current;
	}
	return 0;
}