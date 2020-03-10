#pragma once
#include "../Camera.h"
#include "../Mathlibrary/Mathlibrary.h"
class Transforming : public Camera
{
private:
public:
	vector3 translation;
	vector3 rotation;
	vector3 scaling;
	Quaternion quatrotation;
	Transforming() {
		translation.setVector(0.0f, 0.0f, 0.0f);
		rotation.setVector(0.0f, 0.0f, 0.0f);
		scaling.setVector(1.0f, 1.0f, 1.0f);
		quatrotation.setQuaternion(0.0, 0.0, 0.0, 1.0f);
	};
	~Transforming();
	matrix4f newTransformationMatrix() {
		matrix4f translationmatrix;
		matrix4f rotationmatrix;
		matrix4f quatrotationmatrix;
		matrix4f scalematrix;
		matrix4f camerarotation;
		matrix4f cameratranslation;
		translationmatrix.makeTranslation(translation);
		rotationmatrix.makeRotation(rotation);
		quatrotationmatrix.makeQuatRotation(quatrotation.getForward(), quatrotation.getUp());
		scalematrix.makeScaling(scaling);
		camerarotation.makeCamera(forwardvector, upvector);
		cameratranslation.makeTranslation(-(position.x), -(position.y), -(position.z));
		matrix4f transformationmatrix = translationmatrix * (rotationmatrix * scalematrix);

		/*	if (orthographicprojection == false) {  //world view? */
		matrix4f projectionmatrix;
		projectionmatrix.makeProjection(fov, aspectratiowidth, aspectratioheight, minviewdistance, maxviewdistance);

		return projectionmatrix * (quatrotationmatrix * (cameratranslation * transformationmatrix));
		/*	}
			else {
				return camerarotation * (cameratranslation * transformationmatrix);
			}*/
	}
	matrix4f newUnprojectedMatrix() {
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
		return translationmatrix * (rotationmatrix * scalematrix);
	}
	matrix4f newViewMatrix() {
		matrix4f camerarotation;
		matrix4f cameratranslation;
		camerarotation.makeCamera(forwardvector, upvector);
		cameratranslation.makeTranslation(-(position.x), -(position.y), -(position.z));
		return camerarotation * (cameratranslation * newUnprojectedMatrix());
	}
	matrix4f newProjectionMatrix()
	{
	matrix4f projectionmatrix;
	projectionmatrix.makeProjection(fov, aspectratiowidth, aspectratioheight, minviewdistance, maxviewdistance);
	return projectionmatrix;
}
	matrix4f newSkyboxMatrix() {
		matrix4f translationmatrix;
		matrix4f rotationmatrix;
		matrix4f scalematrix;
		matrix4f camerarotation;
		matrix4f cameratranslation;
		matrix4f projectionmatrix;

		translationmatrix.makeTranslation(translation);
		rotationmatrix.makeRotation(rotation);
		scalematrix.makeScaling(scaling);

		camerarotation.makeCamera(forwardvector, upvector);
		cameratranslation.makeTranslation(-(position.x), -(position.y), -(position.z));

		projectionmatrix.makeProjection(fov, aspectratiowidth, aspectratioheight, minviewdistance, maxviewdistance);

		return projectionmatrix * (camerarotation * (rotationmatrix * scalematrix));
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
	void setTranslationVector(float x, float y, float z) {
		translation.x = x;
		translation.y = y;
		translation.z = z;
	}
	void setRotationVector(float x, float y, float z) {
		rotation.x = x;
		rotation.y = y;
		rotation.z = z;
	}
	void setScalingVector(float x, float y, float z) {
		scaling.x = x;
		scaling.y = y;
		scaling.z = z;
	}

};

