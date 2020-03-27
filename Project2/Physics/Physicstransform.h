#pragma once
#include "../Mathlibrary/Mathlibrary.h"
class Physicstransform  //transform parent + matrix
{
private:
public:
	vector3 position;
	Quaternion rotation;
	Physicstransform() {
		position.setVector(0.0f, 0.0f, 0.0f);
		/*rotation.setVector(0.0f, 0.0f, 0.0f);*/
		rotation.setQuaternion(0.0, 0.0, 0.0, 1.0f);
	};
	~Physicstransform();
	vector3 getPosition() {
		return position;
	}
	Quaternion getRotation() {
		return rotation;
	}
	void setPosition(vector3 newtranslationvector) {
		position = newtranslationvector;
	}
	/*void setRotation(Quaternion newrot) {
		rotation = newrot;
	}*/
	void setPosition(float x, float y, float z) {
		position.x = x;
		position.y = y;
		position.z = z;
	}
	/*void Rotate(vector3 vectorrotation) {
		Quaternion newquat;
		if (vectorrotation.y != 0) {
			newquat = newquat.Rotate(vectorrotation.y, vector3(1.0, 0.0f, 0.0f));
			rotation = newquat.Multiply(rotation);
			rotation = rotation.Normalize();
		}
		if (vectorrotation.x != 0) {
			newquat.setQuaternion(0, 0, 0, 1);
			newquat = newquat.Rotate(vectorrotation.x, vector3(0.f, 1.0f, 0.0f));
			rotation = newquat.Multiply(rotation);
			rotation = rotation.Normalize();
		}
		if (vectorrotation.z != 0) {
			newquat.setQuaternion(0, 0, 0, 1);
			newquat = newquat.Rotate(vectorrotation.z, vector3(0.f, 0.0f, 1.0f));
			rotation = newquat.Multiply(rotation);
			rotation = rotation.Normalize();
		}
	}
	void Rotate(float x, float y, float z) {
		Quaternion newquat;
		if (y != 0) {
			newquat = newquat.Rotate(y, vector3(1.0, 0.0f, 0.0f));
			rotation = newquat.Multiply(rotation);
			rotation = rotation.Normalize();
		}
		if (x != 0) {
			newquat.setQuaternion(0, 0, 0, 1);
			newquat = newquat.Rotate(x, vector3(0.f, 1.0f, 0.0f));
			rotation = newquat.Multiply(rotation);
			rotation = rotation.Normalize();
		}
		if (z != 0) {
			newquat.setQuaternion(0, 0, 0, 1);
			newquat = newquat.Rotate(z, vector3(0.f, 0.0f, 1.0f));
			rotation = newquat.Multiply(rotation);
			rotation = rotation.Normalize();
		}
	}*/
	/*	void setRotation(vector3 vectorrotation) { 
			float todegrees = (180.0f / 3.14159265358979323f);
			vector3 newvec(rotation.x, rotation.y, rotation.z);
			if (vectorrotation != vector3(0, 0, 0)) {
				vectorrotation = vectorrotation.Normalize();
			}
			Rotate(vectorrotation.Subtract(newvec));
		}
		void setRotation(float x, float y, float z) { 
			vector3 vectorrotation(x, y, z);
			if (vectorrotation != vector3(0, 0, 0)) {
				vectorrotation = vectorrotation.Normalize();
			}
			float todegrees = (180.0f/3.14159265358979323f);
			vector3 newvec(rotation.x, rotation.y, rotation.z);
			Rotate(vectorrotation.Subtract(newvec));
		}*/
	void setRotation(Quaternion newrotation) {
		rotation = newrotation;
	}
	void setRotation(float _x, float _y, float _z, float _w) {
		rotation.x = _x;
		rotation.y = _y;
		rotation.z = _z;
		rotation.w = _w;
	}
};



