#pragma once
#include "../Mathlibrary/vector3.h"
#include <vector>
#include "Physicsmanager.h"
#include "Physicsobject.h"
class Raytrace
{
private:
	bool quadraticEquation(float & a, float & b, float & c);
public:
	float t;
	vector3 intersectionpoint;
	//std::vector<Physicsobject *>tracedobjects;
	Physicsobject* tracedobject;
	vector3 normal;
	bool Trace(vector3 start, vector3 end);
	Raytrace();
	~Raytrace();
};

