#pragma once
#include "Light.h"
class Pointlight : public Light
{  //todo: find a good default attenuation value, enginelog that vector isn't -1 < 0 < 1?
public:
	vector3 position;
	float linearterm;
	float quadraticterm;
	float range;
	Pointlight(){
		color = vector3(0.0f, 0.0f, 0.0f);
		position = vector3(0.0f, 0.0f, 0.0f);
		range = 12.0f;
		intensity = 0.0f;
		
		linearterm = .22f;
		quadraticterm = .20f;
	}
	Pointlight(vector3 newcolor, vector3 newposition, float newrange, float newintensity, float newlinearterm, float newquadraticterm) : Light(newcolor, newintensity){
		position = newposition;
		range = newrange;
		linearterm = newlinearterm;
		quadraticterm = newquadraticterm;
	}
	Pointlight(vector3 newcolor, vector3 newposition, float newrange, float newintensity) : Light(newcolor, newintensity) {
		position = newposition;
		range = newrange;
		if (range <= 50) {
			linearterm = .14;
			quadraticterm = .07;
		}
		else if (range <= 120) {
			linearterm = .045;
			quadraticterm = .0075;
		}
		else if (range <= 250) {
			linearterm = 0.022;
			quadraticterm = 0.0019;
		}
		else {
			linearterm = .007;
			quadraticterm = .0002;
		}
	}
	virtual void setLight(vector3 newcolor, vector3 newposition, float newrange, float newintensity, float newlinearterm, float newquadraticterm) {
		color = newcolor;
		range = newrange;
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
	void setRange(float newrange) {
		range = newrange;
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
	float getRange() {
		return range;
	}
	float getLinearTerm() {
		return linearterm;
	}
	float getQuadraticTerm() {
		return quadraticterm;
	}
	virtual ~Pointlight();
};

