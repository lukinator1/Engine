#pragma once
#include "Mathlibrary/Mathlibrary.h"
#include "SDL2/SDL.h"
class Camera	//maybe make this inheret from window?, integrate with skybox	
				//todo: inverted controls
{
private: 
public:
	static vector3 position;
	static vector3 forwardvector;
	static vector3 upvector;
	bool firstperson = false;
	bool mouselook = false;
	bool freeformcamera = false;
	static float fov;
	static float maxviewdistance;
	static float minviewdistance;
	float minzoom;
	float maxzoom;
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
	vector3 getRightVector(){
		vector3 rightvector = upvector.crossProduct(forwardvector).Normalize();
		return rightvector;
	}
	vector3 getLeftVector() {
		vector3 leftvector = forwardvector.crossProduct(upvector).Normalize();
		return leftvector;
	}
	void rotateCamera(vector2 rotation){
		vector3 yaxis = vector3(0.0f, 1.0f, 0.0f);
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

		upvector = forwardvector.crossProduct(horizontalaxis).Normalize();
	}
	void rotateCamera(float y, float x) {
		vector3 yaxis = vector3(0.0f, 1.0f, 0.0f);
		vector3 horizontalaxis;
		if (x != 0.0f){
			x = -x;
			horizontalaxis = yaxis.crossProduct(forwardvector).Normalize();
			forwardvector = forwardvector.Rotate(x, horizontalaxis).Normalize();
		}
		/*upvector = forwardvector.crossProduct(horizontalaxis);  //maybe can take this out
		upvector.Normalize();*/
		if (y != 0.0f) {
			horizontalaxis = yaxis.crossProduct(forwardvector).Normalize();
			forwardvector = forwardvector.Rotate(y, yaxis).Normalize();
		}

		upvector = forwardvector.crossProduct(horizontalaxis).Normalize();
	}
	static vector3 getCameraposition() {
		return position;
	}
	static vector3 getUpvector() {
		return upvector;
	}
	static vector3 getForwardvector() {
		return forwardvector;
	}
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
	void Zoom(int offset) {
		if (fov >= minviewdistance && fov <= maxviewdistance) {
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
		}
	}
	void orthographicProjection(bool project) { //this (probably) won't work as is, need to multiply camera matrix to what's there
		orthographicprojection = project;
	}
	void setMouseLook(bool look) {
		SDL_SetRelativeMouseMode(SDL_TRUE);
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
		firstperson = false;
		upvector = upvector.Normalize();
		forwardvector = forwardvector.Normalize();
	}
	Camera(vector3 newposition) { //check if falls within world space
		position = newposition;
		upvector = vector3(0.0f, 1.0f, 0.0f);
		forwardvector = vector3(0.0f, 0.0f, 1.0f);
	};
	Camera(vector3 newposition, vector3 newupvector, vector3 newforwardvector) { //check if falls within world space
		position = newposition;
		upvector = newupvector;
		forwardvector = newforwardvector;

		upvector = upvector.Normalize();
		forwardvector = forwardvector.Normalize();
	};
	Camera(vector3 newposition, vector3 newupvector, vector3 newforwardvector, float newfov, float max, float min, float w, float h, bool o = false) { //check if falls within world space
		position = newposition;
		upvector = newupvector;
		forwardvector = newforwardvector;
		fov = newfov;
		maxviewdistance = max;
		minviewdistance = min;
		aspectratiowidth = w;
		aspectratioheight = h;
		orthographicprojection = o;

		upvector = upvector.Normalize();
		forwardvector = forwardvector.Normalize();
	};
	~Camera();
};

