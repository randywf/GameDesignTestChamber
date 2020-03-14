#include <iostream>
#include <iomanip>
/**
 * Runge Kutta integration: Simulates the motion of spring oscillation
 * https://gafferongames.com/post/integration_basics/
 */

const float TOLERANCE = 0.001f;

struct State
{
	float x;
	float v;
};

struct Derivative
{
	float dx;
	float dv;
};

float acceleration( const State & state, double t)
{
	// Spring constant, damper
	const float k = 15.0f;
	const float b = 0.1f;
	return -k * state.x - b * state.v;
}

Derivative evaluate( const State & initial, double t, float dt, const Derivative & d )
{
	State state;
	state.x = initial.x + d.dx * dt;
	state.v = initial.v + d.dv * dt;
	
	Derivative output;
	output.dx = state.v;
	output.dv = acceleration(state, t+dt);

	return output;
}

void integrate( State & state, double t, float dt )
{
	Derivative a, b, c, d;

	a = evaluate( state, t, 0.0f, Derivative() );
	b = evaluate( state, t, dt*0.5f, a );
	c = evaluate( state, t, dt*0.5f, b );
	d = evaluate( state, t, dt, c );

	float dxdt = 1.0f / 6.0f * ( a.dx + 2.0f * ( b.dx + c.dx ) + d.dx );
	float dvdt = 1.0f / 6.0f * ( a.dv + 2.0f * ( b.dv + c.dv ) + d.dv );

	state.x = state.x + dxdt * dt;
	state.v = state.v + dvdt * dt;

	return;
}

int main(void)
{
	State example_state = {0.0f, 10.0f};
	double t = 0.0f;
	float dt = 0.01f;
	int s = 0;

	while (t <= 10.0)
	{
		integrate(example_state, t, dt);
		/**
		 * This will print every second
		if (t > ((float)s - TOLERANCE) && t < ((float)s + TOLERANCE)) {
			std::cout << std::fixed << std::setprecision(5);
			std::cout << "t=" << t << "\t";
			std::cout << "position=" << example_state.x << "\t";
			std::cout << "velocity=" << example_state.v << std::endl;
			s++;
		}
		 *
		 */
		std::cout << "time: " << t << "\t";
		std::cout << "pos: " << example_state.x << "\t";
		std::cout << "vel: " << example_state.v << std::endl;
		t += dt;
	}
}