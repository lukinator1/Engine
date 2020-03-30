#pragma once
#include "Physicsobject.h"
class Boundingsphere : public Physicsobject
{
public:
	float radius;
	bool intersectionTest(float _radius, vector3 _position, float &cdistance);
	float calcCollisionDistance(float radius, vector3 position);
	bool Simulate(Physicsobject & physicsobject);
	void Integrate();
	void handleCollision();
	void handleConstraints();
	void recalculateMOI();
	float getRadius();
	Boundingsphere();
	~Boundingsphere();
};