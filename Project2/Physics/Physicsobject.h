#pragma once
#include "../Mathlibrary/vector3.h"
#include "../Rendering/Transforming.h"
#include <vector>
class Physicsobject
{
public:
	enum Shape {
		Sphere,
		Box
	};
	struct Collisiondata {
		bool collided;
		float collisiondistance;
	};
	vector3 velocity;
	vector3 angularvelocity;
	Transforming collidertransform;
	/*vector3 position;*/
	vector3 force;
	vector3 acceleration;
	vector3 angularacceleration;
	float torque;
	float mass;
	float MOI;
	Collisiondata collisiondata;
	std::vector <vector3> forces;
	static float gravity;
	virtual void Simulate(Physicsobject _physicsobject);
	virtual void calculateMOI();
	void setMass(float _mass);
	float getMass();
	Physicsobject();
	~Physicsobject();
};

