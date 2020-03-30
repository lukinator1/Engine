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
vector3 Physicsobject::getPosition()
{
	return collidertransform.getPosition();
}
Quaternion Physicsobject::getRotation()
{
	return collidertransform.getRotation();
}
Transforming Physicsobject::getColliderTransform()
{
	Transforming t;
	t.setPosition(collidertransform.getPosition());
	t.setRotation(collidertransform.getRotation());
	return t;
}
void Physicsobject::setColliderTransform(Transforming & t)
{
	setPosition(t.position);
	setRotation(t.rotation);
}
void Physicsobject::setPosition(vector3 pos) {
	collidertransform.position = pos;
}
void Physicsobject::setRotation(Quaternion rot) {
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
	elasticity = 0.45f;
	oldpos = collidertransform.position;
	tempvel = velocity;
	kineticfrictionconstant = 0.4f;
	/*acceleration.y = acceleration.y - 1100.81f;*/
}
Physicsobject::~Physicsobject()
{
}
float Physicsobject::gravity = 0;
