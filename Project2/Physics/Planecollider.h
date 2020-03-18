#pragma once
#include "../Mathlibrary/vector3.h"
#include "Boundingsphere.h"
class Planecollider
{
public:
	vector3 normal;
	float distance;
	bool collided;
	float collisiondistance;
	float sphereCollision(Boundingsphere &sphere);
	Planecollider();
	~Planecollider();
};

