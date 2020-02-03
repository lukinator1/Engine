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
		matrix4f camerarotation;
		matrix4f cameratranslation;
		translationmatrix.makeTranslation(translation);
		rotationmatrix.makeRotation(rotation);
		scalematrix.makeScaling(scaling);
		camerarotation.makeCamera(forwardvector, upvector);
		cameratranslation.makeTranslation(-(position.x), -(position.y), -(position.z));
		matrix4f transformationmatrix = translationmatrix * (rotationmatrix * scalematrix);
		
		if (orthographicprojection == false) {  //world view?
			matrix4f projectionmatrix; 
			projectionmatrix.makeProjection(fov, aspectratiowidth, aspectratioheight, minviewdistance, maxviewdistance);

			return projectionmatrix * (camerarotation * (cameratranslation * transformationmatrix));
		}
		else {
			return camerarotation * (cameratranslation * transformationmatrix);
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

