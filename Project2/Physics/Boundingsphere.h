#pragma once
#include "../Mathlibrary/vector3.h"
#include "Physicsobject.h"
class Boundingsphere : public Physicsobject
{
public:
	float radius;
	bool boundingSphereCollision(Boundingsphere & othersphere/*, float &collisiondistance*/);
	bool collided;
	float collisiondistance;
	void Simulate(Physicsobject physicsobject);
	Boundingsphere();
	~Boundingsphere();
};