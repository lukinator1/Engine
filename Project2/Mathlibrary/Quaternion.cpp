#include "Quaternion.h"
#include "vector3.h"
Quaternion::Quaternion()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 1.0;
}
Quaternion::Quaternion(float newx, float newy, float newz, float neww)
{
	x = newx;
	y = newy;
	z = newz;
	w = neww;
}
void Quaternion::setQuaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}
void Quaternion::setQuaternion(Quaternion newquat)
{
	*this = newquat;
}
Quaternion Quaternion::Rotate(float angle, vector3 axis) {
	float sinhalfangle = sinf((angle / 2.0f) * (3.14159265358979323f / 180.0f));
	float coshalfangle = cosf((angle / 2.0f) * (3.14159265358979323f / 180.0f));

	float qx = axis.x * sinhalfangle;		//convert matrix -> quaternion
	float qy = axis.y * sinhalfangle;
	float qz = axis.z * sinhalfangle;
	float qw = coshalfangle;
	
	Quaternion newquat(qx, qy, qz, qw);

	return newquat.Normalize();
}
Quaternion Quaternion::Normalize()
{
	float length = sqrt((x * x) + (y * y) + (z * z) + (w * w));
	if (length == 0) {
		engineLog(__FILE__, __LINE__, "A quaternion of length 0 was attempted to be normalized. This is an invalid operation and did not go through.", 3, 3, false);
		return *this;
	}
	else {
		return Quaternion(x / length, y / length, z / length, w / length);
	}
}
Quaternion Quaternion::Conjugate() {
	float newx = -x;
	float newy = -y;
	float newz = -z;
	return Quaternion(newx, newy, newz, this->w);
}
Quaternion Quaternion::Multiply(Quaternion inc)
{
	float myx = x * inc.w + w * inc.x + y * inc.z - z * inc.y;
	float myy = y * inc.w + w * inc.y + z * inc.x - x * inc.z;
	float myz = z * inc.w + w * inc.z + x * inc.y - y * inc.x;
	float myw = w * inc.w - x * inc.x - y * inc.y - z * inc.z;

	Quaternion newquat(myx, myy, myz, myw);
	return newquat;
}
Quaternion Quaternion::Multiply(float incx, float incy, float incz)
{
	float myx = w * incx + y * incz - z * incy;
	float myy = w * incy + z * incx - x * incz;
	float myz = w * incz + x * incy - y * incx;
	float myw = -(x * incx) - (y * incy) - (z * incz);

	Quaternion newquat(myx, myy, myz, myw);
	return newquat;
}
vector3 Quaternion::getForward() {
	return vector3 (2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
	/*vector3 vec(0, 0, 1.0f);
	return vec.quatRotate(*this);*/
}
vector3 Quaternion::getBack() {
	return vector3(-2.0f * (x * z - w * y), -2.0f * (y * z + w * x), -1.0f + 2.0f * (x * x + y * y));
	/*vector3 vec(0, 0, -1.0f);
	return vec.quatRotate(*this);*/
}
vector3 Quaternion::getUp(){
	return vector3(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
	/*vector3 vec(0, 1.0f, 0);
	return vec.quatRotate(*this);*/
}
vector3 Quaternion::getDown(){
	return vector3(-2.0f * (x * y + w * z), -1.0f + 2.0f * (x * x + z * z), -2.0f * (y * z - w * x));
	/*vector3 vec(0, -1.0f, 0);
	return vec.quatRotate(*this);*/
}
vector3 Quaternion::getRight() {
	return vector3(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
	/*vector3 vec(1.0f, 0, 0.0);
	return vec.quatRotate(*this);*/
}
vector3 Quaternion::getLeft() {
	return vector3(-1.0f + 2.0f * (y * y + z * z), -2.0f * (x * y - w * z), -2.0f * (x * z + w * y));
	/*vector3 vec(-1.0f, 0, 0.0);
	return vec.quatRotate(*this);*/
}
/*Quaternion &Quaternion::operator*(const Quaternion &inc)
{
	float myx = x * inc.w + w * inc.x + y * inc.z - z * inc.y;
	float myy = y * inc.w + w * inc.y + z * inc.x - x * inc.z;
	float myz = z * inc.w + w * inc.z + x * inc.y - y * inc.x;
	float myw = w * inc.w - x * inc.x - y * inc.y - z * inc.z;

	Quaternion newquat(myx, myy, myz, myw);
	return newquat;
}
Quaternion &Quaternion::operator=(const Quaternion &inc)
{
	x = inc.x;
	y = inc.y;
	z = inc.z;
	w = inc.w;
	return *this;
}*/
Quaternion::~Quaternion()
{
}
