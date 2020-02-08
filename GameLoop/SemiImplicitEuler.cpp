#include <iostream>
#include <iomanip>
/**
 * Semi-implicit euler calculates the new velocity before position.
 * This results in more accuracy for problems like damped oscillation.
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
		velocity += (force / mass) * dt;
		position += velocity * dt;
		
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