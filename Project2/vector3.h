#pragma once
class vector3 {
public:
	~vector3();
	vector3();
	vector3(float newx, float newy, float newz);
	/*float getX();
	float getY();
	float getZ();*/
	void setVectorThree(float newx, float newy, float newz);
	vector3 crossProduct(vector3 newv);
	float x;
	float y;
	float z;
};

