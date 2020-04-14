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
	bool Simulate(Physicsobject &otherobject);
	void Integrate();
	void handleConstraints();
	void handleCollision();
	std::pair<float, bool> calcCollision(Physicsobject &phy);
	/*void handleConstraints();*/
	void recalculateMOI();
	void setLength(float _length);
	void setWidth(float _width);
	void setHeight(float _height);
	float getLength();
	float getWidth();
	float getHeight();
	void setColliderTransform(Transforming &t);
	void setPosition(vector3 pos);
	void setPosition(float x, float y, float z);
	//void setRotation(Quaternion rot);
	vector3 getMinextents();
	vector3 getMaxextents();
	Boundingbox();
	~Boundingbox();
};

