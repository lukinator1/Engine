#pragma once
#include "Engine.h"
class Camera	//maybe make this inheret from window?
{
private: 
	vector3 position;
	vector3 upvector;
	vector3 forwardvector;
public:
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
	void zoomCamera(float magnitude) {

	}
	void moveCamera(vector3 direction, float distance, float multiplier) {

	}
	vector3 getCameraposition() {
		return position;
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
	Camera();
	~Camera();
};

