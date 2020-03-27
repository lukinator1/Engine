#include "Planecollider.h"
#include <string>

float Planecollider::sphereCollision(Boundingsphere &sphere) {
	float distancefromcenter = normal.dotProduct(sphere.getPosition()) + distance;
	if (distancefromcenter < 0) {  //absolute value
		distancefromcenter = -distancefromcenter;
	}
	collisiondistance = distancefromcenter - sphere.radius;
	if (collisiondistance < 0) {
		collided = true;
	}
	return 0;
}


Planecollider::Planecollider()
{
	/*vector3 position;
	vector3 velocity;
	vector3 movement = deltatime * velocity;
	float radius;*/
}
void Integrate(float deltatime) {

}

Planecollider::~Planecollider()
{
}
