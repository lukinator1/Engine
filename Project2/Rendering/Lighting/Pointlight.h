#pragma once
#include "Light.h"
class Pointlight : public Light
{ 
public:
	vector3 position;
	float linearterm;
	float quadraticterm;
	float range;
public:
	Pointlight(){
		color = vector3(1.0f, 1.0f, 1.0f);
		position = vector3(0.0f, 0.0f, 0.0f);
		range = 26.0f;
		intensity = 0.75f;
		
		linearterm = .19f;
		quadraticterm = .16f;
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
		if (range <= 50.0f) {
			linearterm = .12f;
			quadraticterm = .05f;
		}
		else if (range <= 120.0f) {
			linearterm = .040f;
			quadraticterm = .007f;
		}
		else if (range <= 250.0f) {
			linearterm = 0.020f;
			quadraticterm = 0.0017f;
		}
		else {
			linearterm = .006f;
			quadraticterm = .0001f;
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

