#pragma once
#include "vector3.h"
class Light //default constructors?
{
public:
	vector3 color;
	float intensity;
	Light(vector3 newlightcolor, float newintensity) {
		color = newlightcolor.Normalize();
		intensity = newintensity;
	}
	Light(vector3 newlightcolor) {
		color = newlightcolor.Normalize();
		intensity = 0.0f;
	}
	void setLight(vector3 newcolor, float newintensity) {
		color = newcolor.Normalize();
		intensity = newintensity;
	}
	void setLight(Light newlight) {
		*this = newlight;
	}
	void setColor(vector3 newcolor) {
		color = newcolor.Normalize();
	}
	void setIntensity(float newintensity) {
		intensity = newintensity;
	}
	vector3 getColor() {
		return color;
	}
	float getIntensity() {
		return intensity;
	}
	virtual ~Light();
};

