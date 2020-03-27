#pragma once
#include "Physicsobject.h"
class Boundingsphere : public Physicsobject
{
public:
	float radius;
	/*bool Simulate(Boundingsphere & othersphere/*, float &collisiondistance);*/
	bool intersectionTest(float _radius, vector3 _position);
	bool Simulate(Physicsobject & physicsobject);
	void Integrate();
	void handleCollision();
	void handleConstraints();
	void setMOI(float _MOI);
	float getMOI();
	void recalculateMOI();
	float getRadius();
	Boundingsphere();
	~Boundingsphere();
};