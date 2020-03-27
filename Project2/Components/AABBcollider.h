#pragma once
#include "Component.h"
#include "../Physics/Physicsmanager.h"
class AABBcollider
{
public:
	bool Simulate(Physicsobject & othersphere/*, float &collisiondistance*/);
	bool intersectionTest(float _radius, vector3 _position);
	void Simulate(Physicsobject physicsobject);
	void Integrate();
	void handleCollision();
	void handleConstraints();
	void setMOI(float _MOI);
	float getMOI();
	void calculateMOI();
	AABBcollider();
	~AABBcollider();
};

