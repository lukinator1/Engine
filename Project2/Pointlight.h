#pragma once
#include "Light.h"
class Pointlight : public Light
{  //todo: find a good default attenuation value, enginelog that vector isn't -1 < 0 < 1?
public:
	vector3 position;
	float linearterm;
	float quadraticterm;
	Pointlight(){
		color = vector3(0.0f, 0.0f, 0.0f);
		intensity = 0.0f;
		position = vector3(0.0f, 0.0f, 0.0f);
		linearterm = .22;
		quadraticterm = .20;
	}
	Pointlight(vector3 newcolor, vector3 newposition, float newintensity, float newlinearterm, float newquadraticterm) : Light(newcolor, newintensity){
		position = newposition;
		linearterm = newlinearterm;
		quadraticterm = newquadraticterm;
	}
	virtual void setLight(vector3 newcolor, vector3 newposition, float newintensity, float newlinearterm, float newquadraticterm) {
		color = newcolor;
		intensity = newintensity;
		position = newposition;
		linearterm = newlinearterm;
		quadraticterm = newquadraticterm;
	}
	virtual void setLight(Pointlight plight) {
		*this = plight;
	}
	void setPosition(vector3 newposition) {
		position = newposition;
	}
	void setLinearTerm(float newlinearterm) {
		linearterm = newlinearterm;
	}
	void setQuadraticTerm(float newquadraticterm) {
		quadraticterm = newquadraticterm;
	}
	vector3 getPosition() {
		return position;
	}
	float getLinearTerm() {
		return linearterm;
	}
	float getQuadraticTerm() {
		return quadraticterm;
	}
	virtual ~Pointlight();
};

