#include "Boundingsphere.h"
void Boundingsphere::boundingSphereCollision(Boundingsphere &othersphere/*, float &collisiondistance*/) {
	float radiusdistance = radius + othersphere.radius;
	float centerdistance = (othersphere.collidertransform.position.Subtract(collidertransform.position)).Magnitude();
	float collisiondistance = centerdistance - radiusdistance;
	if (centerdistance < radiusdistance) {
		collisiondata.clear();
		momentia.clear();
		forces.clear();
		collided = true;
		collisiondata.push_back(Collisiondata(collisiondistance, &othersphere));
		std::pair <float, vector3> momentum = { othersphere.mass, othersphere.velocity };
		momentia.push_back(momentum);
		forces.push_back(othersphere.acceleration.multiply(othersphere.mass));
	}
	else {
		collided = false;
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
	collided = false;
	MOI = (2.0f / 5.0f) * mass * radius * radius;
}


Boundingsphere::~Boundingsphere()
{
}
