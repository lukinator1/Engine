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
	collisiondata.forces.push_back(vector3(0, gravity, 0));
	elasticity = 1.0f;
	oldpos = collidertransform.position;
	tempvel = velocity;
	/*acceleration.y = acceleration.y - 1100.81f;*/
}
Physicsobject::~Physicsobject()
{
}
float Physicsobject::gravity = 0;
