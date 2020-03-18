#pragma once
#include "../Mathlibrary/vector3.h"
#include "../Rendering/Transforming.h"
class Physicsobject
{
public:
	enum Shape {
		Sphere,
		Box
	};
	vector3 velocity;
	vector3 angularvelocity;
	Transforming collidertransform;
	/*vector3 position;*/
	vector3 force;
	vector3 acceleration;
	float mass;
	float torque;
	int shape;
	virtual void Simulate(Physicsobject _physicsobject);
	Physicsobject();
	~Physicsobject();
};

