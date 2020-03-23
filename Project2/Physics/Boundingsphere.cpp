#include "Boundingsphere.h"
void Boundingsphere::boundingSphereCollision(Boundingsphere &othersphere/*, float &collisiondistance*/){
	float radiusdistance = radius + othersphere.radius;
	float centerdistance = (othersphere.collidertransform.position.Subtract(collidertransform.position)).Magnitude();
	float collisiondistance = centerdistance - radiusdistance;
	if (centerdistance < radiusdistance) {
		collided = true;
		collisiondata.collisiondistance = collisiondistance;
		collisiondata.otherobjects.push_back(&othersphere);
		std::pair <float, vector3> momentum = { othersphere.mass, othersphere.velocity };
		collisiondata.momentia.push_back(momentum);
		collisiondata.forces.push_back(acceleration.multiply(mass));
	}
	else {
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
