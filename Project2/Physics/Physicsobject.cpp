#include "Physicsobject.h"

void Physicsobject::Integrate()
{
}

bool Physicsobject::Simulate(Physicsobject & _physicsobject)
{
	return false;
}

void Physicsobject::handleCollision()
{
}

void Physicsobject::recalculateMOI()
{
}

float Physicsobject::getRadius()
{
	return 0;
}
vector3 Physicsobject::getMinextents() {
	return vector3(0, 0, 0);
}
vector3 Physicsobject::getMaxextents() {
	return vector3(0, 0, 0);
}
void Physicsobject::setPosition(vector3 pos) {
	collidertransform.position = pos;
}
void Physicsobject::setRotation(vector3 rot) {
	collidertransform.rotation = rot;
}
void Physicsobject::handleConstraints()
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
	collided = false;
	collisiondata.forces.push_back(vector3(0, gravity, 0));
	elasticity = 0.0f;
	oldpos = collidertransform.position;
	tempvel = velocity;
	kineticfrictionconstant = 0.4f;
	/*acceleration.y = acceleration.y - 1100.81f;*/
}
Physicsobject::~Physicsobject()
{
}
float Physicsobject::gravity = 0;
