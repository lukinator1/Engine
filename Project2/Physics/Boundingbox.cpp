#include "Boundingbox.h"
float Boundingbox::boundingBoxCollision(Boundingbox & otherbox) {
	vector3 difference = otherbox.minextents.Subtract(maxextents);
	vector3 otherdifference = minextents.Subtract(otherbox.maxextents);
	vector3 distance;
	if (difference.x > otherdifference.x) {
		distance.x = difference.x;
	}
	else {
		distance.x = otherdifference.x;
	}
	if (difference.y > otherdifference.y) {
		distance.y = difference.y;
	}
	else {
		distance.y = otherdifference.y;
	}
	if (difference.z > otherdifference.z) {
		distance.z = difference.z;
	}
	else {
		distance.z = otherdifference.z;
	}
	maxdistance = distance.x;
	if (distance.y > maxdistance) {
		maxdistance = distance.y;
	}
	if (distance.z > maxdistance) {
		maxdistance = distance.z;
	}

	if (maxdistance < 0) {
		collided = true;
	}
	return 0;
}


Boundingbox::Boundingbox()
{
}


Boundingbox::~Boundingbox()
{
}
