#pragma once
#include "Camera.h"
#include "Engine.h"
class Transforming : public Camera
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

		
		if (orthographicprojection == false) {
			matrix4f projectionmatrix; 
			projectionmatrix.makeProjection(fov, aspectratiowidth, aspectratioheight, minviewdistance, maxviewdistance);
			return projectionmatrix * (translationmatrix * (rotationmatrix * scalematrix));
		}
		else {
			return translationmatrix * (rotationmatrix * scalematrix);
		}
	}	
	void setPerspectiveProjectionSettings(float newfov, float newwidth, float newheight, float newminviewdistance, float newmaxviewdistance) {
		fov = newfov;
		aspectratiowidth = newwidth;
		aspectratioheight = newheight;
		minviewdistance = newminviewdistance;
		maxviewdistance = newmaxviewdistance;
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

