#pragma once
#include "../../Mathlibrary/vector3.h"
class Light //default constructors?
{
public:
	vector3 color;
	float intensity;
	Light() {
		color = vector3(1.0f, 1.0f, 1.0f);
		intensity = .75f;
	}
	Light(vector3 newlightcolor, float newintensity) {
		color = newlightcolor;
		intensity = newintensity;
	}
	Light(vector3 newlightcolor) {
		color = newlightcolor;
		intensity = 0.0f;
	}
	void setLight(vector3 newcolor, float newintensity) {
		color = newcolor;
		intensity = newintensity;
	}
	void setLight(Light newlight) {
		*this = newlight;
	}
	void setColor(vector3 newcolor) {
		color = newcolor;
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
	void deleteLight() {

	}
	~Light();
};

