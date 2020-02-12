#pragma once
#include <math.h>
#include "Quaternion.h"
#include "Logger.h"
class vector3 : public Logger {
public:
	~vector3();
	vector3();
	vector3(float newx, float newy, float newz);
	/*float getX();
	float getY();
	float getZ();*/
	void setVectorThree(float newx, float newy, float newz);
	vector3 Rotate(float angle, vector3 axis);
	vector3 crossProduct(vector3 newv);
	vector3 Normalize();
	float x;
	float y;
	float z;
	vector3 add(vector3 addedvector);
	vector3 add(float adder);
	vector3 multiply(vector3 multiplier);
	vector3 multiply(float multiplier);
	vector3 subtract(vector3 sub);
	vector3 subtract(float sub);
	bool operator!= (vector3 rhs);
};

