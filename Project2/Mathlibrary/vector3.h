#pragma once
#include <math.h>
#include "vector2.h"
#include "Quaternion.h"
#include "../Logger.h"
class vector3 : public Logger { //todo: overloads
public:
	~vector3();
	vector3();
	vector3(float newx, float newy, float newz);
	/*float getX();
	float getY();
	float getZ();*/
	void setVector(float newx, float newy, float newz);
	float Magnitude();
	float dotProduct(vector3 vec);
	vector3 Rotate(float angle, vector3 axis);
	vector3 quatRotate(Quaternion quat);
	vector3 crossProduct(vector3 newv);
	vector3 Normalize();
	float x;
	float y;
	float z;
	vector3 add(vector3 addedvector);
	vector3 add(float adder);
	vector3 multiply(vector3 multiplier);
	vector3 multiply(float multiplier);
	vector3 divide(vector3 d);
	vector3 divide(float d);
	vector3 Subtract(vector3 sub);
	vector3 Subtract(float sub);
	vector3 negativeVector();
	vector3 negateVector();
	vector3 absValue();
	vector2 getXY();
	vector2 getYX();
	vector2 getYZ();
	vector2 getZY();
	vector2 getZX();
	vector2 getXZ();
	vector3 interpolateVector(vector3 destination, float interpfactor);
	bool operator!= (vector3 rhs);
	bool operator==(vector3 rhs);
	vector3 operator*(vector3 rhs);
	vector3 operator+(vector3 rhs);
	vector3 operator+=(vector3 rhs);
	vector3 operator-(vector3 rhs);
	vector3 operator/(vector3 rhs);
};

