#pragma once
#include "../Camera.h"
#include "../Mathlibrary/Mathlibrary.h"
class Transforming : public Camera //transform parent + matrix
{
private:
public:
	vector3 translation;
	/*vector3 rotation;*/
	vector3 scaling;
	Quaternion rotation;
	Transforming() {
		translation.setVector(0.0f, 0.0f, 0.0f);
		/*rotation.setVector(0.0f, 0.0f, 0.0f);*/
		scaling.setVector(1.0f, 1.0f, 1.0f);
		rotation.setQuaternion(0.0, 0.0, 0.0, 1.0f);
	};
	~Transforming();
	matrix4f newTransformationMatrix() {
		matrix4f projectionmatrix;
		matrix4f unprojected;
		matrix4f camerarotationmatrix;
		matrix4f cameratranslation;
		/*matrix4f translationmatrix;
		matrix4f rotationmatrix;
		matrix4f quatrotationmatrix;
		matrix4f scalematrix;*/
		/*translationmatrix.makeTranslation(translation);
		/*rotationmatrix.makeRotation(rotation);
		quatrotationmatrix.makeQuatRotation(quatrotation.getForward(), quatrotation.getUp(), quatrotation.getRight());
		scalematrix.makeScaling(scaling);
		matrix4f transformationmatrix = translationmatrix * ( /*rotationamtrix quatrotationmatrix * scalematrix);*/
		unprojected = newUnprojectedMatrix();
		camerarotationmatrix.makeQuatRotation(camerarotation);
		cameratranslation.makeTranslation(-(position.x), -(position.y), -(position.z));
		projectionmatrix.makeProjection(fov, aspectratiowidth, aspectratioheight, minviewdistance, maxviewdistance);
		/*	if (orthographicprojection == false) { */

		return projectionmatrix * (camerarotationmatrix * (cameratranslation * unprojected));

		/*	}
			else {
				return camerarotation * (cameratranslation * transformationmatrix);
			}*/
	}
	matrix4f newUnprojectedMatrix() {
		matrix4f translationmatrix;
		matrix4f rotationmatrix;
		matrix4f quatrotationmatrix;
		matrix4f scalematrix;
		translationmatrix.makeTranslation(translation);
		/*rotationmatrix.makeRotation(rotation);*/
		quatrotationmatrix.makeQuatRotation(rotation);
		scalematrix.makeScaling(scaling);
		return translationmatrix * (quatrotationmatrix * scalematrix);
	}
	matrix4f newViewMatrix() {
		matrix4f camerarotationmatrix;
		matrix4f cameratranslation;
		camerarotationmatrix.makeQuatRotation(camerarotation);
		cameratranslation.makeTranslation(-(position.x), -(position.y), -(position.z));
		return camerarotationmatrix * (cameratranslation * newUnprojectedMatrix());
	}
	matrix4f newProjectionMatrix()
	{
	matrix4f projectionmatrix;
	projectionmatrix.makeProjection(fov, aspectratiowidth, aspectratioheight, minviewdistance, maxviewdistance);
	return projectionmatrix;
}
	matrix4f newSkyboxMatrix(/*bool infinitelyscaling*/) {
		/*matrix4f translationmatrix;*/
		matrix4f rotationmatrix;
		matrix4f scalematrix;
		matrix4f camerarotationmatrix;
		matrix4f quatrotationmatrix;
		/*matrix4f cameratranslation;*/
		matrix4f projectionmatrix;

		/*translationmatrix.makeTranslation(translation);
		rotationmatrix.makeRotation(rotation);*/
		quatrotationmatrix.makeQuatRotation(rotation);
		scalematrix.makeScaling(scaling);
		camerarotationmatrix.makeQuatRotation(camerarotation);
		/*cameratranslation.makeTranslation(-(position.x), -(position.y), -(position.z));*/
		projectionmatrix.makeProjection(fov, aspectratiowidth, aspectratioheight, minviewdistance, maxviewdistance);

		return projectionmatrix * (camerarotationmatrix * (quatrotationmatrix * scalematrix));

		/*if (infinitelyscaling) {
			return projectionmatrix * (camerarotationmatrix * (quatrotationmatrix * scalematrix));
		}
		else {
			return projectionmatrix * (cameratranslation * (camerarotationmatrix * (translationmatrix * (quatrotationmatrix * scalematrix))));
		}*/
	}
	matrix4f newTextMatrix() {
		matrix4f textmatrix;
		textmatrix.makeOrthographic(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0); //needs to be changed to window width
		return textmatrix;
	}

	void setPerspectiveProjectionSettings(float newfov, float newwidth, float newheight, float newminviewdistance, float newmaxviewdistance) {
		fov = newfov;
		aspectratiowidth = newwidth;
		aspectratioheight = newheight;
		minviewdistance = newminviewdistance;
		maxviewdistance = newmaxviewdistance;
	}
	vector3 getPosition() {
		return translation;
	}
	Quaternion getRotation() {
		return rotation;
	}
	vector3 getScale() {
		return scaling;
	}
	void setPosition(vector3 newtranslationvector){
		translation = newtranslationvector;
		}
	/*void setRotation(vector3 newrotationvector) {
		rotation = newrotationvector;
	}*/
	void setScale(vector3 newscalingvector) {
		scaling = newscalingvector;
	}
	void setPosition(float x, float y, float z) {
		translation.x = x;
		translation.y = y;
		translation.z = z;
	}
	/*void setRotationVector(float x, float y, float z) {
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}*/
	void setRotation(vector3 vectorrotation) {
		Quaternion newquat;
		if (vectorrotation.y != 0) {
			newquat = newquat.Rotate(vectorrotation.y, vector3(1.0, 0.0f, 0.0f));
			rotation = newquat.Multiply(rotation);
			rotation = rotation.Normalize();
		}
		if (vectorrotation.x != 0){
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
	void setRotation(float x, float y, float z) {
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
	}
	void setQuatRotation(Quaternion newquatrotation) {
		rotation = newquatrotation;
	}
	void setQuatRotation(float _x, float _y, float _z, float _w) {
		rotation.x = _x;
		rotation.y = _y;
		rotation.z = _z;
		rotation.w = _w;
	}
	void setScalingVector(float x, float y, float z) {
		scaling.x = x;
		scaling.y = y;
		scaling.z = z;
	}

};

