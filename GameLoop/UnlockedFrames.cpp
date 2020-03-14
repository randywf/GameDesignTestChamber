#include <ctime>
#include <iomanip>
#include <iostream>

const int ONE_SECOND = 1000000000; // nano seconds in one second

int main(void)
{
	timespec current, previous;
	int ticker;
	int elapsed_ns = 0;
	int accumulator = 0;
	short first_loop = 1;

	clock_gettime(CLOCK_MONOTONIC, &previous);
	while (1) {
		ticker = 0;
		while (accumulator < ONE_SECOND) {
			// Loop runs until one second has passed
			clock_gettime(CLOCK_MONOTONIC, &current);
			if (current.tv_sec == previous.tv_sec) {
				// No need to borrow for subtracting (e.g. 1.6 seconds - 1.3 seconds)
				elapsed_ns = current.tv_nsec - previous.tv_nsec;
			}
			else {
				// When current time and previous time aren't in the same second,
				// current nanoseconds may be less than previous. (e.g 2.1 seconds - 1.9 seconds)
				elapsed_ns = current.tv_nsec + (current.tv_sec - previous.tv_sec) * ONE_SECOND - previous.tv_nsec;
			}
			// Store seconds passed in this iteration in a sum of all iterations so far
			accumulator += elapsed_ns;
			ticker++;
			previous = current;
		}
		// Keep any surplus time as a 'debt' for the next iteration
		accumulator -= ONE_SECOND;

		std::cout << "Ticks per second:" << ticker << std::endl;
	}
	return 0;
}