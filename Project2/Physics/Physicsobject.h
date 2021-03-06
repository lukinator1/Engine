#pragma once
#include "../Mathlibrary/vector3.h"
#include "Physicstransform.h"
#include "../Rendering/Transforming.h"
#include <vector>
class Physicsobject //0 = sphere, 1 = AABB
{
public:
	struct Collisiondata {
		float collisiondistance;
		/*Collisiondata(float distance, Physicsobject* other, vector3 force) {
			collisiondistance = distance;
			 otherobjects.push_back(other);
		}*/
		std::vector<vector3> intersectionpoints;
		std::vector<vector3> intersectionnormals;
		std::vector<Physicsobject *> otherobjects;
		std::vector<vector3> forces;
		std::vector <std::pair<float, vector3>> momentia;
	};
	Physicstransform collidertransform;
	unsigned int shape;
	vector3 velocity;
	vector3 angularvelocity;
	/*vector3 position;*/
	vector3 oldpos;
	vector3 tempvel;
	vector3 tempoldpos;
	vector3 acceleration;
	vector3 angularacceleration;
	float mass;
	float MOI;
	float momentum;
	float kineticfrictionconstant;
	float elasticity;
	bool collided;
	bool terrain = false;
	Collisiondata collisiondata;
	static vector3 gravity;
	virtual void Integrate();
	virtual bool Simulate(Physicsobject &_physicsobject);
	virtual void handleCollision();
	virtual void recalculateMOI();
	virtual float getRadius();
	vector3 getPosition();
	Quaternion getRotation();
	Transforming getColliderTransform();
	virtual void setColliderTransform(Transforming &t);
	virtual void setPosition(vector3 pos);
	virtual void setPosition(float x, float y, float z);
	virtual void setRotation(Quaternion rot);
	virtual vector3 getMinextents();
	virtual vector3 getMaxextents();
	virtual void handleConstraints();
	void setMass(float _mass);
	float getMass();
	Physicsobject();
	~Physicsobject();
};

