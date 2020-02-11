#pragma once
#include "Light.h"
#include "vector3.h"
class Spotlight : public Light	//default constructors where don't need to add terms
{
public:
	vector3 position;
	vector3 direction;
	float range;
	float cutoff;
	float linearterm;
	float quadraticterm;
	Spotlight() {
		color = vector3(0.0f, 0.0f, 0.0f);
		position = vector3(0.0f, 0.0f, 0.0f);
		direction = vector3(1.0f, 0.0, 0.0f);
		range = 12.0f;
		cutoff = 45.0f;
		intensity = 0.0f;
		linearterm = .22f;
		quadraticterm = .20f;
	}
	Spotlight(vector3 newcolor, vector3 newposition, vector3 newdirection, float newrange, float newcutoff, float newintensity, float newlinearterm, float newquadraticterm) : Light(newcolor, newintensity) {
		position = newposition;
		direction = newdirection.Normalize();
		range = newrange;
		cutoff = newcutoff;
		linearterm = newlinearterm;
		quadraticterm = newquadraticterm;
	}
	virtual void setLight(vector3 newcolor, vector3 newposition, vector3 newdirection, float newrange, float newcutoff, float newintensity, float newlinearterm, float newquadraticterm) {
		color = newcolor;
		direction = newdirection.Normalize();
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
		direction = newdirection.Normalize();
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

