#include "Physicsobject.h"



void Physicsobject::Simulate(Physicsobject _physicsobject)
{
}

Physicsobject::Physicsobject()
{
	mass = 10.0f;
	torque = 0.0f;
	acceleration = acceleration.Subtract(9.8f);
}
Physicsobject::~Physicsobject()
{
}
