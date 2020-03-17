#pragma once
#include "../Mathlibrary/vector3.h"
class Boundingsphere
{
public:
	vector3 center;
	float radius;
	float boundingSphereCollision(Boundingsphere & othersphere);
	bool intersected;
	float intersectiondistance;
	Boundingsphere();
	~Boundingsphere();
};

