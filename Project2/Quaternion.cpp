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
	if (length == 0) {
		/*engineLog(__FILE__, __LINE__, "The stack allocator wassn't created, the alignment must be a power of 2, => 2 and <= 256. A nullptr was returned instead.", 3, 1, false);*/
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
Quaternion::~Quaternion()
{
}
