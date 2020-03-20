#pragma once
#include "Physicsobject.h"
class Boundingsphere : public Physicsobject
{
public:
	float radius;
	void boundingSphereCollision(Boundingsphere & othersphere/*, float &collisiondistance*/);
	void Simulate(Physicsobject physicsobject);
	void setMOI(float _MOI);
	float getMOI();
	void calculateMOI();
	Boundingsphere();
	~Boundingsphere();
};