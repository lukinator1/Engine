#pragma once
#include "Engine.h"
class Transforming
{
private:

public:
	vector3 translation;
	vector3 rotation;
	vector3 scaling;
	Transforming() {
		translation.setVectorThree(0.0f, 0.0f, 0.0f);
		rotation.setVectorThree(0.0f, 0.0f, 0.0f);
		scaling.setVectorThree(1.0f, 1.0f, 1.0f);
	};
	~Transforming();
	matrix4f newTransformationMatrix() {
		matrix4f translationmatrix;
		matrix4f rotationmatrix;
		matrix4f scalematrix;
		translationmatrix.makeTranslation(translation);
		rotationmatrix.makeRotation(rotation);
		scalematrix.makeScaling(scaling);
		return translationmatrix * (rotationmatrix * scalematrix);
	}

	vector3 getTranslationVector() {
		return translation;
	}
	vector3 getRotationVector() {
		return rotation;
	}
	vector3 getScalingVector() {
		return scaling;
	}
	void setTranslationVector(vector3 newtranslationvector){
		translation = newtranslationvector;
		}
	void setRotationVector(vector3 newrotationvector) {
		rotation = newrotationvector;
	}
	void setScalingVector(vector3 newscalingvector) {
		scaling = newscalingvector;
	}

};

