#include "Quaternion.h"
Quaternion::Quaternion(float newx, float newy, float newz, float neww)
{
	x = newx;
	y = newy;
	z = newz;
	w = neww;
}
Quaternion Quaternion::Normalize()
{
	float length = sqrt((x * x) + (y * y) + (z * z) + (w * w));
	x /= length;
	y /= length;
	z /= length;
	w /= length;
	return *this;
}
Quaternion Quaternion::Conjugate() {
	x = -x;
	y = -y;
	z = -z;
	return *this;
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
Quaternion Quaternion::Multiply(float x, float y, float z)
{
	float myx = w * x + y * z - z * y;
	float myy = w * y + z * x - x * z;
	float myz = w * z + x * y - y * x;
	float myw = -x * x - y * y - z * z;

	Quaternion newquat(myx, myy, myz, myw);
	return newquat;
}
Quaternion::~Quaternion()
{
}
