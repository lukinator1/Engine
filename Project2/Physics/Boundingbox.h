#pragma once
#include "../Mathlibrary/vector3.h"
class Boundingbox
{
public:
	vector3 minextents;
	vector3 maxextents;
	bool interesected;
	float maxdistance = 0;
	float boundingBoxCollision(Boundingbox & otherbox);
	Boundingbox();
	~Boundingbox();
};

