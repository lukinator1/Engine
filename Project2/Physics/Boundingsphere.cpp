#include "Boundingsphere.h"

void Boundingsphere::boundingSphereCollision(Boundingsphere &othersphere/*, float &collisiondistance*/) {
	float radiusdistance = radius + othersphere.radius;
	float centerdistance = (othersphere.collidertransform.position.Subtract(collidertransform.position)).Magnitude();
	collisiondata.collisiondistance = centerdistance - radiusdistance;
	if (centerdistance < radiusdistance) {
		collisiondata.collided = true;
	}
	else {
		collisiondata.collided = false;
	}
}

void Boundingsphere::Simulate(Physicsobject physicsobject)
{
}

void Boundingsphere::setMOI(float _MOI) {
	MOI = _MOI;
}
float Boundingsphere::getMOI()
{
	return MOI;
}
void Boundingsphere::calculateMOI() {
	MOI = (2.0f / 5.0f) * mass * radius * radius;
}
Boundingsphere::Boundingsphere()
{
	radius = 20.0f;
	collisiondata.collided = false;
	collisiondata.collisiondistance = 0.0f;
	MOI = (2.0f / 5.0f) * mass * radius * radius;
}


Boundingsphere::~Boundingsphere()
{
}
