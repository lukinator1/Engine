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
		float collisiondistance;
		/*Collisiondata(float distance, Physicsobject* other, vector3 force) {
			collisiondistance = distance;
			 otherobjects.push_back(other);
		}*/
		std::vector<Physicsobject *> otherobjects;
		std::vector<vector3> forces;
		std::vector <std::pair<float, vector3>> momentia;
	};
	vector3 velocity;
	vector3 angularvelocity;
	Transforming collidertransform;
	/*vector3 position;*/
	vector3 oldpos;
	vector3 force;
	vector3 acceleration;
	vector3 angularacceleration;
	float torque;
	float mass;
	float MOI;
	float momentum;
	float frictionconstant;
	float elasticity;
	bool collided;
	vector3 resultingdirection;
	Collisiondata collisiondata;
	static float gravity;
	virtual void Simulate(Physicsobject _physicsobject);
	virtual void calculateMOI();
	void setMass(float _mass);
	float getMass();
	Physicsobject();
	~Physicsobject();
};

