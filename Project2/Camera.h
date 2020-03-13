#pragma once
#include "Mathlibrary/Mathlibrary.h"
#include "SDL2/SDL.h"
class Camera	//maybe make this inheret from window?	
{
private: 
public:
	static vector3 position;
	/*static vector3 forwardvector;
	static vector3 upvector;*/
	static Quaternion camerarotation;
	static float fov;
	static float maxviewdistance;
	static float minviewdistance;
	static float aspectratiowidth;
	static float aspectratioheight;
	static bool orthographicprojection;
	void setCameraPosition(vector3 newcameraposition) {
		position = newcameraposition;
	}
	void setCameraPosition(float newx, float newy, float newz) {
		position.x = newx;
		position.y = newy;
		position.z = newz;
	}
	void setCameraDirection() {

	} //todo
	void zoomCamera(float magnitude) {

	}
	void moveCamera(vector3 direction, float distance) {
		position = position.add(direction.multiply(distance));
	}
	/*vector3 getRightVector(){
		vector3 rightvector = upvector.crossProduct(forwardvector).Normalize();
		return rightvector;
	}
	vector3 getLeftVector() {
		vector3 leftvector = forwardvector.crossProduct(upvector).Normalize();
		return leftvector;
	}*/
	void rotateCamera(vector2 rotation){
		/*vector3 yaxis = vector3(0.0f, 1.0f, 0.0f);
		vector3 horizontalaxis;
		if (rotation.x != 0.0f) {
			rotation.x = -rotation.x;
			horizontalaxis = yaxis.crossProduct(forwardvector).Normalize();
			forwardvector.Rotate(rotation.x, horizontalaxis).Normalize();
		}

		if (rotation.y != 0.0f) {
			horizontalaxis = yaxis.crossProduct(forwardvector).Normalize();
			forwardvector.Rotate(rotation.y, yaxis).Normalize();
		}

		upvector = forwardvector.crossProduct(horizontalaxis).Normalize();*/
		vector3 yaxis = vector3(0.0f, 1.0f, 0.0f);
		vector3 horizontalaxis = camerarotation.getRight();
		Quaternion quat;

		if (rotation.y != 0.0f) {

			quat = quat.Rotate(rotation.y, horizontalaxis);
			camerarotation = (camerarotation).Multiply(quat);
			camerarotation = camerarotation.Normalize();
		}

		Quaternion otherquat;
		if (rotation.x != 0.0f) {
			otherquat = otherquat.Rotate(-rotation.y, yaxis);
			camerarotation = camerarotation.Multiply(otherquat);
			camerarotation = camerarotation.Normalize();
		}
	/*	if (rotation.y != 0.0f) {
			rotation.y = -rotation.y;
			horizontalaxis = yaxis.crossProduct(camerarotation.getForward()).Normalize();
			camerarotation = camerarotation.Multiply(quat.Rotate(rotation.y, horizontalaxis));
		}

		if (rotation.x != 0.0f) {
			camerarotation = camerarotation.Multiply(quat.Rotate(rotation.x, yaxis));
		}*/

	}
	void rotateCamera(float flippedy, float flippedx) {
		/*vector3 yaxis = vector3(0.0f, 1.0f, 0.0f);
		vector3 horizontalaxis;
		Quaternion quat;
		if (flippedx != 0.0f){
			flippedx = -flippedx;
			horizontalaxis = yaxis.crossProduct(forwardvector).Normalize();

			float sinhalfangle = sinf((flippedx / 2.0f) * (3.14159265358979323f / 180.0f));
			float coshalfangle = cosf((flippedx / 2.0f) * (3.14159265358979323f / 180.0f));

			float qx = horizontalaxis.x * sinhalfangle;		//convert matrix -> quaternion
			float qy = horizontalaxis.y * sinhalfangle;
			float qz = horizontalaxis.z * sinhalfangle;
			float qw = coshalfangle;

			Quaternion rotation(qx, qy, qz, qw);
			Quaternion rotationconjugate = rotation.Conjugate();

			Quaternion newquat = (rotation.Multiply(forwardvector.x, forwardvector.y, forwardvector.z)).Multiply(rotationconjugate);
			camerarotation = newquat;
			camerarotation = camerarotation.Normalize();
			forwardvector.setVector(newquat.x, newquat.y, newquat.z);
			forwardvector = forwardvector.Normalize();
			/*forwardvector = forwardvector.Rotate(flippedx, horizontalaxis).Normalize();
		}
		Quaternion otherquat;
		if (flippedy != 0.0f) {
			horizontalaxis = yaxis.crossProduct(forwardvector).Normalize();

			otherquat = otherquat.Rotate(-flippedy, yaxis);
			camerarotation = otherquat.Multiply(camerarotation);
			camerarotation = camerarotation.Normalize();
		}*/
	    /*	if (flippedy != 0.0f) {
			horizontalaxis = yaxis.crossProduct(forwardvector).Normalize();
			forwardvector = forwardvector.Rotate(flippedy, yaxis).Normalize();
		}

		upvector = forwardvector.crossProduct(horizontalaxis).Normalize();*/

		vector3 yaxis = vector3(0.0f, 1.0f, 0.0f);
		vector3 horizontalaxis = camerarotation.getRight();
		Quaternion quat;

		if (flippedx != 0.0f) {

			quat = quat.Rotate(flippedx, horizontalaxis);
			camerarotation = (camerarotation).Multiply(quat);
			camerarotation = camerarotation.Normalize();
		}

		Quaternion otherquat;
		if (flippedy != 0.0f) {
			otherquat = otherquat.Rotate(-flippedy, yaxis);
			camerarotation = camerarotation.Multiply(otherquat);
			camerarotation = camerarotation.Normalize();
		}
	}
	static vector3 getCameraposition() {
		return position;
	}
/*	static vector3 getUpvector() {
		return upvector;
	}
	static vector3 getForwardvector() {
		return forwardvector;
	}*/
	void setAspectRatio(float newheight, float newwidth) {
		aspectratioheight = newheight;
		aspectratiowidth = newwidth;
	}
	void setMaxViewDistance(float newmaxviewdistance) {
		maxviewdistance = newmaxviewdistance;
	}
	void setMinViewDistance(float newminviewdistance) {
		minviewdistance = newminviewdistance;
	}
	void setFov(float newfov) {
		fov = newfov;
	}
	void Zoom(float offset) {
		if (fov - offset < minviewdistance) {
			fov = minviewdistance;
		}
		else if (fov - offset > maxviewdistance) {
			fov = maxviewdistance;
		}
		else {
			fov -= offset;
		}
		/*if (fov >= minviewdistance && fov <= maxviewdistance) {
			fov -= offset;
		}
		else if (fov < minviewdistance) {
			fov = minviewdistance;
		}
		else if (fov > maxviewdistance) {
			fov = maxviewdistance;
		}
		else if (fov == minviewdistance && offset <= 0) {
			fov -= offset;
		}
		else if (fov == maxviewdistance && offset >= 0) {
			fov -= offset;
		}*/
	}
	void orthographicProjection(bool project) { //this (probably) won't work as is, need to multiply camera matrix to what's there
		orthographicprojection = project;
	}
	void setMouseLook(bool look) {
		if (look == true) {
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
		else if (look == false) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}
	void cameraStartup(float _fov, float _maxviewdistance, float _minviewdistance, float arwidth, float arheight) {
		fov = _fov;
		maxviewdistance = _maxviewdistance;
		minviewdistance = _minviewdistance;
		aspectratiowidth = arwidth;
		aspectratioheight = arheight;
	}
	/*void handleMessage(Message &message){
		if (!messagequeue.empty()) {
			switch (message.messagetype) {
			case Message::Messagetypes::Keydown:
				switch (message.messagedataone) {
				case 26:					//w
					moveCamera(forwardvector, .3f);

					break;
				case 4:
					moveCamera(forwardvector, -.3f);
					break;
				case 22:
					moveCamera(forwardvector, -.3f);
					break;
				case 7:
					moveCamera(, 0.3);
					break;

				case 80:
					rotateCamera(-0.3f, 0.0f);
					break;
				case 82:
					rotateCamera(0.0f, 0.3f);
					break;
				case 81:
					rotateCamera(0.0f, -0.3f);
					break;
				case 79:
					rotateCamera(0.3f, 0.0f);
					break;
				}
			}
	}
}*/

	Camera() {
		/*upvector = upvector.Normalize();
		forwardvector = forwardvector.Normalize();
		camerarotation.Normalize();*/
	}
	Camera(vector3 newposition) { //check if falls within world space
		position = newposition;
		camerarotation = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
		/*upvector = vector3(0.0f, 1.0f, 0.0f);
		forwardvector = vector3(0.0f, 0.0f, 1.0f);*/
	};
	Camera(vector3 newposition, vector3 newupvector, vector3 newforwardvector) {
		position = newposition;
		/*upvector = newupvector;
		forwardvector = newforwardvector;

		upvector = upvector.Normalize();
		forwardvector = forwardvector.Normalize();*/
	};
	Camera(vector3 newposition, vector3 newupvector, vector3 newforwardvector, float newfov, float max, float min, float w, float h, bool o = false) { 
		position = newposition;
		/*upvector = newupvector;
		forwardvector = newforwardvector;*/
		fov = newfov;
		maxviewdistance = max;
		minviewdistance = min;
		aspectratiowidth = w;
		aspectratioheight = h;
		orthographicprojection = o;

		/*upvector = upvector.Normalize();
		forwardvector = forwardvector.Normalize();*/
	};
	~Camera();
};

