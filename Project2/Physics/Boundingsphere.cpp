#include "Boundingsphere.h"

float Boundingsphere::boundingSphereCollision(Boundingsphere & othersphere) {
	float radiusdistance = radius + othersphere.radius;
	float centerdistance = (othersphere.center.Subtract(center)).Magnitude();
	if (centerdistance < radiusdistance) {
		intersected = true;
	}
	else {
		intersected = false;
	}
	intersectiondistance = centerdistance - radiusdistance;
}

Boundingsphere::Boundingsphere()
{
}


Boundingsphere::~Boundingsphere()
{
}
