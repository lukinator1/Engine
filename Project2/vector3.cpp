#include "vector3.h"
vector3::vector3()
{
	x = 0;
	y = 0;
	z = 0;
}
vector3::vector3(float newx, float newy, float newz)
{
	x = newx;
	y = newy;
	z = newz;
}
/*float vector3::getX()
{
	return x;
}
float vector3::getY()
{
	return y;
}
float vector3::getZ()
{
	return z;
}*/
void vector3::setVectorThree(float newx, float newy, float newz) {
	x = newx;
	y = newy;
	z = newz;
}
vector3 vector3::Rotate(float angle, vector3 axis) {
	float sinhalfangle = sin((angle / 2.0f) * (3.14159265358979323f / 180));
	float coshalfangle = cos((angle / 2.0f) * (3.14159265358979323f / 180));

	float qx = axis.x * sinhalfangle;		//convert matrix -> quaternion
	float qy = axis.y * sinhalfangle;
	float qz = axis.z * sinhalfangle;
	float qw = coshalfangle;
	
	Quaternion rotation(qx, qy, qz, qw);
	Quaternion rotationconjugate = rotation.Conjugate();

	Quaternion newquat = (rotation.Multiply(x,y,z)).Multiply(rotationconjugate);
	x = newquat.x;
	y = newquat.y;
	z = newquat.z;

	return *this;
}
vector3 vector3::crossProduct(vector3 newv) {
	float myx = (y * newv.z) - (z * newv.y);
	float myy = (z * newv.x) - (x * newv.z);
	float myz = (x * newv.y) - (y * newv.x);
	return vector3(myx, myy, myz);
}
vector3 vector3::Normalize() {
	float length = sqrt((x * x) + (y * y) + (z * z));
	x /= length;
	y /= length;
	z /= length;
	return *this;
}
vector3 vector3::add(vector3 adder)
{
	x += adder.x;
	y += adder.y;
	z += adder.z;
	return *this;
}
vector3 vector3::add(float adder)
{
	x += adder;
	y += adder;
	z += adder;
	return *this;
}
vector3 vector3::multiply(vector3 multiplier)
{
	x = x * multiplier.x;
	y = y * multiplier.y;
	z = z * multiplier.z;
	return *this;
}
vector3 vector3::multiply(float multiplier)
{
	x = x * multiplier;
	y = y * multiplier;
	z = z * multiplier;
	return *this;
}
vector3::~vector3()
{
}

