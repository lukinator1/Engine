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
	float x;
	float y;
	float z;
};

