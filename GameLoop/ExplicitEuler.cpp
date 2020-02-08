#include <iostream>
#include <iomanip>
/**
 * Numerical integration using a fixed timestep (explicit euler)
 * Only accurate over a fixed rate of change. However, since the velocity
 * is not fixed, the final position has an error (e.g. 450 vs. 500). Setting
 * timestep as a small value makes this error tolerable.
 * https://gafferongames.com/post/integration_basics/
 */

const float TOLERANCE = 0.001f;

// Update position and velocity from force, mass, and time interval
int main(void)
{
	// Time, delta-time
	double t = 0.0f;
	float dt = 0.01f;
	// Integer second
	int s = 0;

	float velocity = 0.0f;
	float position = 0.0f;
	float force = 10.0f;
	float mass = 1.0f;

	while (t <= 10.0)
	{
		position += velocity * dt;
		velocity += (force / mass) * dt;
		
		if (t > ((float)s - TOLERANCE) && t < ((float)s + TOLERANCE)) {
			std::cout << std::fixed << std::setprecision(5);
			std::cout << "t=" << t << "\t";
			std::cout << "position=" << position << "\t";
			std::cout << "velocity=" << velocity << std::endl;
			s++;
		}

		t += dt;
	}
}