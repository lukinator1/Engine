#include "vector3.h"
vector3::vector3()
{
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
vector3 vector3::crossProduct(vector3 newv) {
	float myx = (y * newv.z) - (z * newv.y);
	float myy = (z * newv.x) - (x * newv.z);
	float myz = (x * newv.y) - (y * newv.x);
	return vector3(myx, myy, myz);
}
vector3::~vector3()
{
}

