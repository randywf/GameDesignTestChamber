#include <ctime>
#include <iomanip>
#include <iostream>
/**
 * This game loop creates a clamp on physics calculation tick rate while
 * allowing unlimited render frame rate. There is a physics loop inside of the
 * main loop that is only run once a certain amount of time has passed. Renders
 * occur every time the main loop is run. This prevents physics errors due to
 * the timestep being too small.
 * Conversely, if the main loop is running too slowly (i.e. graphics rendering
 * is slowing the program down), the inner physics loop will iterate more often
 * than the main loop in order to keep errors out of the physics calculations
 * that would be caused by a large timestep (caused by the slow rendering).
 */

const int ONE_SECOND = 1000000000; // Conversion factor seconds to nanoseconds
const int TICKRATE_LO = 10; // Tick rate not allowed below this threshold
const int TICKRATE_HI = 100; // Tick rate not allowed above this threshold
const int NS_BOUND_HI = ONE_SECOND / TICKRATE_LO; // Upper nanosecond bound
const int NS_BOUND_LO = ONE_SECOND / TICKRATE_HI; // Lower nanosecond bound

int main(void)
{
	timespec current, previous;
	int elapsed_ns, accumulator;
	int gfx_ticker, phys_ticker, seconds;
	short first_loop;

	clock_gettime(CLOCK_MONOTONIC, &previous);
	accumulator = 0;
	phys_ticker = 0;
	gfx_ticker = 0;
	seconds = 0;
	first_loop = 1;

	while (1) {
		clock_gettime(CLOCK_MONOTONIC, &current);

		if (first_loop == 1) {
			first_loop = 0;
		}
		else {
			// Calculate the elapsed time as long as this is not the first loop
			if (current.tv_sec == previous.tv_sec) {
				elapsed_ns = current.tv_nsec - previous.tv_nsec;
			}
			else {
				elapsed_ns = (
					(current.tv_sec - previous.tv_sec) * ONE_SECOND
					+ current.tv_nsec - previous.tv_nsec
				);
			}
			// Clamp the elapsed time at the defined upper bound if necessary
			// This will cause the game to slow down below real time, but
			// will avoid physics update bottlenecks.
			if (elapsed_ns > NS_BOUND_HI) {
				elapsed_ns = NS_BOUND_HI;
			}
			accumulator += elapsed_ns;
			seconds += elapsed_ns;
		}

		while (accumulator >= NS_BOUND_LO) {
			// This is where the physics function would go
			accumulator -= NS_BOUND_LO;
			phys_ticker++;
		}

		// This is where the rendering function would go
		previous = current;
		gfx_ticker++;

		// Display number of physics and graphics updates every second
		if (seconds > ONE_SECOND && first_loop != 1) {
			std::cout << "gfx:  " << gfx_ticker << std::endl;
			std::cout << "phys: " << phys_ticker << std::endl;
			gfx_ticker = 0;
			phys_ticker = 0;
			seconds -= ONE_SECOND;
		}
	}
	return 0;
}