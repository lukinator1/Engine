#pragma once
#include "Window.h"
class Camera
{
public:
	static float fov;
	static float maxviewdistance;
	static float minviewdistance;
	static float aspectratiowidth;
	static float aspectratioheight;
	static bool orthographicprojection;
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

