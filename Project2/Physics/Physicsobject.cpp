#include "Physicsobject.h"



void Physicsobject::Simulate(Physicsobject _physicsobject)
{
}

void Physicsobject::calculateMOI()
{
}

void Physicsobject::setMass(float _mass)
{
	mass = _mass;
}

float Physicsobject::getMass()
{
	return mass;
}

Physicsobject::Physicsobject()
{
	mass = 10.0f;
	torque = 0.0f;
	forces.push_back(vector3(0, gravity, 0));
	/*acceleration.y = acceleration.y - 1100.81f;*/
}
Physicsobject::~Physicsobject()
{
}
float Physicsobject::gravity = 0;
