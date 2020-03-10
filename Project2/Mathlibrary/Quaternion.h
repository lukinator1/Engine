#pragma once
#include <math.h>
#include "../Logger.h"
class vector3;
class Quaternion : public Logger
{
public:
	float x;
	float y;
	float z;
	float w;
	Quaternion Normalize();
	Quaternion Conjugate();
	Quaternion Multiply(Quaternion multiplier);
	Quaternion Multiply(float x, float y, float z);
	vector3 getForward();
	vector3 getBack();
	vector3 getUp();
	vector3 getDown();
	vector3 getRight();
	vector3 getLeft();
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	void setQuaternion(float _x, float _y, float _z, float _w);
	~Quaternion();
};

