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
	state.x = initial.x + d.dx;
	state.v = initial.v + d.dv;
	
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

	state.x += dxdt * dt;
	state.v += dvdt * dt;

	return;
}