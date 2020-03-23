#include "Raytrace.h"


bool Raytrace::Trace(vector3 start, vector3 end) { //end is actually direction
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
	t = -1;
	vector3 l;
	float a = end.dotProduct(end);
	float b;
	float c;
	float newt = 0;
	bool traced = false;
	/*vector3 bsqr = b * b; (start * start * end * end).multiply(4.0f);
	vector3 discriminant;*/
	for (int i = 0; i < spherecolliders.size(); i++) {
		/*discriminant = bsqr.Subtract(((start * start).Subtract(spherecolliders[i]->radius * spherecolliders[i]->radius) * a).multiply(4.0f));*/
		l = start - spherecolliders[i]->collidertransform.position;
		b = 2.0f * end.dotProduct(l);
		c = l.dotProduct(l) - spherecolliders[i]->radius;
		if (quadraticEquation(a, b, c, newt)) {
			traced = true;
			if (newt < t || t == -1) {
				t = newt;
				intersectionpoint = start + end.multiply(t);
				tracedobject = spherecolliders[i];
				normal = intersectionpoint - spherecolliders[i]->collidertransform.position;
				normal = normal.Normalize();
			}
		}
	}

	if (traced) {
		return true;
	}
	t = -1;
	tracedobject = nullptr;
	normal = vector3(0.0, 0.0, 0.0);
	intersectionpoint = vector3(0.0, 0.0, 0.0);
	return false;
}
bool Raytrace::Trace(vector3 start, vector3 end, std::vector<Physicsobject *> ignore) { //end is actually direction
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
	t = -1;
	vector3 l;
	float a = end.dotProduct(end);
	float b;
	float c;
	float newt = 0;
	bool traced = false;
	bool ig = false; 
	/*vector3 bsqr = b * b; (start * start * end * end).multiply(4.0f);
	vector3 discriminant;*/
	for (int i = 0; i < spherecolliders.size(); i++) {
		ig = false;
		for (int u = 0; u < ignore.size(); u++) {
			if (ignore[u] == spherecolliders[i]) {
				ig = true;
			}
		}
		if (ig == true) {
			continue;
		}
		/*discriminant = bsqr.Subtract(((start * start).Subtract(spherecolliders[i]->radius * spherecolliders[i]->radius) * a).multiply(4.0f));*/
		l = start - spherecolliders[i]->collidertransform.position;
		b = 2.0f * end.dotProduct(l);
		c = l.dotProduct(l) - spherecolliders[i]->radius;
		if (quadraticEquation(a, b, c, newt)) {
			traced = true;
			if (newt < t || t == -1) {
				t = newt;
				intersectionpoint = start + end.multiply(t);
				tracedobject = spherecolliders[i];
				normal = intersectionpoint - spherecolliders[i]->collidertransform.position;
				normal = normal.Normalize();
			}
		}
	}

	if (traced) {
		return true;
	}
	t = -1;
	tracedobject = nullptr;
	normal = vector3(0.0, 0.0, 0.0);
	intersectionpoint = vector3(0.0, 0.0, 0.0);
	return false;
}
bool Raytrace::Trace(vector3 start, vector3 end, Boundingsphere * sphereobject) {
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
	vector3 l;
	float a = end.dotProduct(end);
	float b;
	float c;
	float newt = 0;
	/*vector3 bsqr = b * b; (start * start * end * end).multiply(4.0f);
	vector3 discriminant;*/
	/*discriminant = bsqr.Subtract(((start * start).Subtract(spherecolliders[i]->radius * spherecolliders[i]->radius) * a).multiply(4.0f));*/
	l = start - sphereobject->collidertransform.position;
	b = 2.0f * end.dotProduct(l);
	c = l.dotProduct(l) - sphereobject->radius;
	if (quadraticEquation(a, b, c, newt)) {
		t = newt;
		intersectionpoint = start + end.multiply(t);
		tracedobject = sphereobject;
		normal = intersectionpoint - sphereobject->collidertransform.position;
		normal = normal.Normalize();
		return true;
		}
	else {
		t = -1;
		tracedobject = nullptr;
		normal = vector3(0.0, 0.0, 0.0);
		intersectionpoint = vector3(0.0, 0.0, 0.0);
		return false;
	}
}
bool Raytrace::Trace(vector3 start, vector3 end, vector3 position, float radius) {
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
	vector3 l;
	float a = end.dotProduct(end);
	float b;
	float c;
	float newt = 0;
	/*vector3 bsqr = b * b; (start * start * end * end).multiply(4.0f);
	vector3 discriminant;*/
	/*discriminant = bsqr.Subtract(((start * start).Subtract(spherecolliders[i]->radius * spherecolliders[i]->radius) * a).multiply(4.0f));*/
	l = start - position;
	b = 2.0f * end.dotProduct(l);
	c = l.dotProduct(l) - radius;
	if (quadraticEquation(a, b, c, newt)) {
		t = newt;
		intersectionpoint = start + end.multiply(t);
		tracedobject = nullptr;
		normal = intersectionpoint - position;
		normal = normal.Normalize();
		return true;
	}
	else {
		t = -1;
		tracedobject = nullptr;
		normal = vector3(0.0, 0.0, 0.0);
		intersectionpoint = vector3(0.0, 0.0, 0.0);
		return false;
	}
}

bool Raytrace::quadraticEquation(float &a, float &b, float &c, float &t) {
	float discrimenant = (b * b) - (4.0f  * a * c);
	if (discrimenant < 0) {  //no collision
		return false;
	}
	else if (discrimenant > 0) { //collided on 2 points but only returning first
		float q = b >= 0 ? -0.5f * (b + sqrt(discrimenant)) : -0.5f * (b - sqrt(discrimenant));
		float x0 = q / a;
		float x1 = c / q;
		if ((x0 < x1 || x1 < 0) && (x0 >= 0)) {
			t = x0;
			return true;
		}
		else if ((x1 < x0 || x0 < 0) && (x1 >= 0)) {
			t = x1;
			return true;
		}
		else {
			return false;
		}

		
	}
	else {  //collided with 1
		float q = -0.5f * b / a;
		if (q >= 0) {
			t = -0.5f * b / a;
			return true;
		}
		else {
			return false;
		}
	}
}

Raytrace::Raytrace()
{
	t = -1;
}


Raytrace::~Raytrace()
{
}
