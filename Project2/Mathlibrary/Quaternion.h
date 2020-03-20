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
	Quaternion Add(Quaternion inc);
	Quaternion Multiply(Quaternion multiplier);
	Quaternion Multiply(float , float y, float z);
	Quaternion Multiply(float inc);
	vector3 getForward();
	vector3 getBack();
	vector3 getUp();
	vector3 getDown();
	vector3 getRight();
	vector3 getLeft();
	/*Quaternion & operator*(const Quaternion & inc);*/
	Quaternion & operator=(const Quaternion &inc);
	Quaternion();
	Quaternion(float x, float y, float z, float w);
	void setQuaternion(float _x, float _y, float _z, float _w);
	void setQuaternion(Quaternion newquat);
	float Magnitude();
	Quaternion Rotate(float angle, vector3 axis);
	~Quaternion();
};

