#pragma once
#include "../Mathlibrary/vector3.h"
#include <vector>
#include "Physicsmanager.h"
#include "Physicsobject.h"
class Raytrace //todo: normalize t
{
private:
	bool quadraticEquation(float & a, float & b, float & c, float &t);
public:
	float t;
	vector3 intersectionpoint;
	//std::vector<Physicsobject *>tracedobjects;
	Physicsobject* tracedobject;
	vector3 normal;
	bool Trace(vector3 start, vector3 direction);
	bool Trace(vector3 start, vector3 end, std::vector<Physicsobject *> ignore);
	bool Trace(vector3 start, vector3 direction, Physicsobject *ignore);
	bool Trace(vector3 start, vector3 end, vector3 position, float radius);
	Raytrace();
	~Raytrace();
};

