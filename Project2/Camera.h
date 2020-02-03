#pragma once
#include "Engine.h"
class Camera	//maybe make this inheret from window?
{
private: 
public:
	static vector3 position;
	static vector3 forwardvector;
	static vector3 upvector;
	bool firstperson;
	bool keypressed = false;
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
	void rotateCamera(vector3 rotation){
		rotation.y = -rotation.y;
		rotation.x = -rotation.x;
		vector3 yaxis = vector3(0.0f, 1.0f, 0.0f);
		vector3 horizontalaxis = yaxis.crossProduct(forwardvector);
		horizontalaxis.Normalize();

		forwardvector.Rotate(rotation.x, horizontalaxis);
		forwardvector.Normalize();
		upvector = forwardvector.crossProduct(horizontalaxis);  //maybe can take this out
		upvector.Normalize();


		horizontalaxis = yaxis.crossProduct(forwardvector);
		horizontalaxis.Normalize();

		forwardvector.Rotate(rotation.y, yaxis);
		forwardvector.Normalize();
		upvector = forwardvector.crossProduct(horizontalaxis);
		upvector.Normalize();
	}
	void rotateCamera(float y, float x) {
		y = -y;
		x = -x;
		vector3 yaxis = vector3(0.0f, 1.0f, 0.0f);
		vector3 horizontalaxis = yaxis.crossProduct(forwardvector);
		horizontalaxis.Normalize();

		forwardvector.Rotate(x, horizontalaxis);
		forwardvector.Normalize();
		upvector = forwardvector.crossProduct(horizontalaxis);  //maybe can take this out
		upvector.Normalize();


		horizontalaxis = yaxis.crossProduct(forwardvector);
		horizontalaxis.Normalize();

		forwardvector.Rotate(y, yaxis);
		forwardvector.Normalize();
		upvector = forwardvector.crossProduct(horizontalaxis);
		upvector.Normalize();
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
	void orthographicProjection(bool project) {
		orthographicprojection = project;
	}
	void handleMessage(Message &message){
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
					/*moveCamera(, 0.3);*/
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
}
	Camera() {
		firstperson = false;
		upvector.Normalize();
		forwardvector.Normalize();
	}
	Camera(vector3 newposition, vector3 newupvector, vector3 newforwardvector) { //check if falls within world space
		position = newposition;
		upvector = newupvector;
		forwardvector = newforwardvector;

		upvector.Normalize();
		forwardvector.Normalize();
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

		upvector.Normalize();
		forwardvector.Normalize();
	};
	~Camera();
};

