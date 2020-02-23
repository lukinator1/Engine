#pragma once
#include "Light.h"
class Directionallight : public Light
{	public:
	vector3 direction;
	Directionallight(vector3 newlightcolor, vector3 newdirection, float newintensity) : Light(newlightcolor, newintensity){
			direction = newdirection.Normalize();
	}
	Directionallight(vector3 newlightcolor, vector3 newdirection) : Light(newlightcolor) {
			direction = newdirection.Normalize();
	}
	virtual void setLight(vector3 newcolor, vector3 newdirection, float newintensity) {
		color = newcolor;
		direction = newdirection.Normalize();
		intensity = newintensity;
	}
	virtual void setLight(Directionallight newlight) {
		*this = newlight;
	}
	/*void setColor(vector3 newcolor) {
		color = newcolor;
	}*/
	void setDirection(vector3 newdirection) {
			direction = newdirection.Normalize();
	}
	/*void setIntensity(float newintensity) {
		intensity = newintensity;
	}*/
	/*vector3 getColor() {
		return color;
	}*/
	vector3 getDirection() {
		return direction;
	}
	/*float getIntensity() {
		return intensity;
	}*/
	~Directionallight();
};

