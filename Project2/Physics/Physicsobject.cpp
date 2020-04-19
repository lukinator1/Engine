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
void Physicsobject::setPosition(float x, float y, float z)
{
	collidertransform.setPosition(x, y, z);
}
void Physicsobject::setRotation(Quaternion rot) {
	collidertransform.rotation = rot;
	collidertransform.rotation = collidertransform.rotation.Normalize();
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
	mass = 20.0f;
	collided = false;
	collisiondata.forces.push_back(gravity);
	elasticity = 0.45f;
	oldpos = collidertransform.position;
	tempvel = velocity;
	kineticfrictionconstant = 0.4f;
	/*acceleration.y = acceleration.y - 1100.81f;*/
}
Physicsobject::~Physicsobject()
{
}
vector3 Physicsobject::gravity = vector3(0, 0, 0);
