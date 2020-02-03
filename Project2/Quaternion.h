#pragma once
#include <math.h>
class vector3;
class Quaternion;
class Quaternion
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
	Quaternion(float x, float y, float z, float w);
	~Quaternion();
};

