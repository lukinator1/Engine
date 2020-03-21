#pragma once
#include "../Mathlibrary/vector3.h"
#include <vector>
#include "Physicsmanager.h"
#include "Physicsobject.h"
class Raytrace
{
public:
	float t;
	bool Trace(vector3 start, vector3 end);
	Raytrace();
	~Raytrace();
};

