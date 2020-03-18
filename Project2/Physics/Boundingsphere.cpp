#include "Boundingsphere.h"

bool Boundingsphere::boundingSphereCollision(Boundingsphere &othersphere/*, float &collisiondistance*/) {
	float radiusdistance = radius + othersphere.radius;
	float centerdistance = (othersphere.collidertransform.position.Subtract(othersphere.collidertransform.position)).Magnitude();
	collisiondistance = centerdistance - radiusdistance;
	if (centerdistance < radiusdistance) {
		collided = true;
		return true;
	}
	else {
		collided = false;
		return false;
	}
}

void Boundingsphere::Simulate(Physicsobject physicsobject)
{
}

Boundingsphere::Boundingsphere()
{
	shape = Physicsobject::Sphere;
	radius = 20.0f;
	collided = false;
	collisiondistance = 0.0f;
}


Boundingsphere::~Boundingsphere()
{
}
