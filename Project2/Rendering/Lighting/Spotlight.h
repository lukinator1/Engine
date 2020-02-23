#pragma once
#include "Light.h"
class Spotlight : public Light
{
public: 
	vector3 position;
	vector3 direction;
	float range;
	float cutoff;
	float linearterm;
	float quadraticterm;
public:
	Spotlight() {
		color = vector3(1.0f, 1.0f, 1.0f);
		position = vector3(0.0f, 0.0f, 0.0f);
		direction = vector3(1.0f, 1.0, 1.0f);
		range = 16.0f;
		cutoff = 45.0f;
		intensity = 0.75f;
		linearterm = .19f;
		quadraticterm = .16f;
	}
	Spotlight(vector3 newcolor, vector3 newposition, vector3 newdirection, float newrange, float newcutoff, float newintensity, float newlinearterm, float newquadraticterm) : Light(newcolor, newintensity) {
		position = newposition;
		if (newdirection != vector3(0.0f, 0.0f, 0.0f)) {
			direction = newdirection.Normalize();
		}
		range = newrange;
		cutoff = newcutoff;
		linearterm = newlinearterm;
		quadraticterm = newquadraticterm;
	}
	virtual void setLight(vector3 newcolor, vector3 newposition, vector3 newdirection, float newrange, float newcutoff, float newintensity, float newlinearterm, float newquadraticterm) {
		color = newcolor;
		if (newdirection != vector3(0.0f, 0.0f, 0.0f)) {
			direction = newdirection.Normalize();
		}
		range = newrange;
		cutoff = newcutoff;
		intensity = newintensity;
		position = newposition;
		linearterm = newlinearterm;
		quadraticterm = newquadraticterm;
	}
	virtual void setLight(Spotlight slight) {
		*this = slight;
	}
	void setPosition(vector3 newposition) {
		position = newposition;
	}
	void setDirection(vector3 newdirection) {
		if (newdirection != vector3(0.0f, 0.0f, 0.0f)) {
			direction = newdirection.Normalize();
		}
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
	vector3 getDirection() {
		return direction;
	}
	float getRange() {
		return range;
	}
	float getCutoff() {
		return cutoff;
	}
	float getLinearTerm() {
		return linearterm;
	}
	float getQuadraticTerm() {
		return quadraticterm;
	}
	~Spotlight();
};

