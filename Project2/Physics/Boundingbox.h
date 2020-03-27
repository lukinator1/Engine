#pragma once
#include "../Mathlibrary/vector3.h"
#include "Physicsobject.h"
#include "Raytrace.h"
class Boundingbox : public Physicsobject
{
	vector3 minextents;
	vector3 maxextents;
	float length;
	float width;
	float height;
public:
	float maxdistance = 0;
	float boundingBoxCollision(Boundingbox & otherbox);
	bool Simulate(Physicsobject &otherobject);
	void Integrate();
	void handleCollision();
	void recalculateMOI();
	void setLength(float _length);
	void setWidth(float _width);
	void setHeight(float _height);
	float getLength();
	float getWidth();
	float getHeight();
	Boundingbox();
	~Boundingbox();
};

