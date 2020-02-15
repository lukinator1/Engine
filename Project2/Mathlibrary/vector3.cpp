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
	/*x = x / length;
	y = y / length;
	z = z / length;
	return *this;*/
	if (length == 0) {
		/*engineLog(__FILE__, __LINE__, "A direction vector of 0, 0, 0 was passed in. This is undefined behavior and may break related code as 0, 0, 0 doesn't have a direction. ", 3, 3, true);*/
		return *this;
	}
	else return vector3(x / length, y / length, z / length);
}
vector3 vector3::add(vector3 adder)
{
	/*x = x + adder.x;
	y = y + adder.y;
	z = z + adder.z;
	return *this;*/
	return vector3(x + adder.x, y + adder.y, z + adder.z);
}
vector3 vector3::add(float adder)
{
	/*x = x + adder;
	y = y + adder;
	z = z + adder;
	return *this;*/
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
	/*x = x * multiplier;
	y = y * multiplier;
	z = z * multiplier;
	return *this;*/
	return vector3(x * multiplier, y * multiplier, z * multiplier);
}
vector3 vector3::subtract(vector3 sub) {
	return vector3(x - sub.x, y - sub.y, z - sub.z);
}
vector3 vector3::subtract(float sub) {
	return vector3(x - sub, y - sub, z - sub);
}
vector2 vector3::getXY()
{
	return vector2(x, y);
}
vector2 vector3::getYX()
{
	return vector2(y, x);
}
vector2 vector3::getYZ()
{
	return vector2(y, z);
}
vector2 vector3::getZY()
{
	return vector2(z, y);
}
vector2 vector3::getZX()
{
	return vector2(z, x);
}
vector2 vector3::getXZ()
{
	return vector2(x, z);
}
vector3 vector3::interpolateVector(vector3 destination, float interpfactor) {
	return destination.subtract(*this).multiply(interpfactor).add(*this);
}
bool vector3::operator!=(vector3 rhs)
{
	if (x == rhs.x && y == rhs.y && z == rhs.z) {
		return false;
	}
	else {
		return true;
	}
}
vector3::~vector3()
{
}

