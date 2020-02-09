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
	float sinhalfangle = sinf((angle / 2.0f) * (3.14159265358979323f / 180.0f));
	float coshalfangle = cosf((angle / 2.0f) * (3.14159265358979323f / 180.0f));

	float qx = axis.x * sinhalfangle;		//convert matrix -> quaternion
	float qy = axis.y * sinhalfangle;
	float qz = axis.z * sinhalfangle;
	float qw = coshalfangle;
	
	Quaternion rotation(qx, qy, qz, qw);
	Quaternion rotationconjugate = rotation.Conjugate();

	Quaternion newquat = (rotation.Multiply(x,y,z)).Multiply(rotationconjugate);
	vector3 newvector(newquat.x, newquat.y, newquat.z);

	/*x = newquat.x;
	y = newquat.y;
	z = newquat.z;*/

	return newvector;
	/*return *this;*/
}
vector3 vector3::crossProduct(vector3 newv) {
	float myx = (y * newv.z) - (z * newv.y);
	float myy = (z * newv.x) - (x * newv.z);
	float myz = (x * newv.y) - (y * newv.x);
	return vector3(myx, myy, myz);
}
vector3 vector3::Normalize() {
	float length = sqrt((x * x) + (y * y) + (z * z));
	return vector3(x/length, y/length, z/length);
}
vector3 vector3::add(vector3 adder)
{
	return vector3(x + adder.x, y + adder.y, z + adder.z);
}
vector3 vector3::add(float adder)
{
	return vector3(x + adder, y + adder, z + adder);
}
vector3 vector3::multiply(vector3 multiplier)
{
	/*x = x * multiplier.x;
	y = y * multiplier.y;
	z = z * multiplier.z;
	return *this;*/
	return vector3(x * multiplier.x, y * multiplier.y, z * multiplier.z);
}
vector3 vector3::multiply(float multiplier)
{
	return vector3(x * multiplier, y * multiplier, z * multiplier);
}
vector3 vector3::subtract(vector3 sub) {
	return vector3(x - sub.x, y - sub.y, z - sub.z);
}
vector3 vector3::subtract(float sub) {
	return vector3(x - sub, y - sub, z - sub);
}
vector3::~vector3()
{
}

