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
	for (int i = 0; i < colliders.size(); i++) {
		switch (colliders[i]->shape) {
		case 0: //sphere
			l = start - colliders[i]->getPosition();
			b = 2.0f * end.dotProduct(l);
			c = l.dotProduct(l) - (colliders[i]->getRadius() * colliders[i]->getRadius());
			if (quadraticEquation(a, b, c, newt)) {
				traced = true;
				if (newt < t || t == -1) {
					t = newt;
					intersectionpoint = start + end.multiply(t);
					tracedobject = colliders[i];
					normal = intersectionpoint - colliders[i]->getPosition();
					normal = normal.Normalize();
				}
			}
		case 1: //box

		break;
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
	for (int i = 0; i < colliders.size(); i++) {
		ig = false;
		for (int u = 0; u < ignore.size(); u++) {
			if (ignore[u] == colliders[i]) {
				ig = true;
			}
		}
		if (ig == true) {
			continue;
		}
		switch (colliders[i]->shape) {
		case 0:
			l = start - colliders[i]->getPosition();
			b = 2.0f * end.dotProduct(l);
			c = l.dotProduct(l) - (colliders[i]->getRadius() * colliders[i]->getRadius());
			if (quadraticEquation(a, b, c, newt)) {
				traced = true;
				if (newt < t || t == -1) {
					t = newt;
					intersectionpoint = start + end.multiply(t);
					tracedobject = colliders[i];
					normal = intersectionpoint - colliders[i]->getPosition();
					normal = normal.Normalize();
				}
			}
		case 1: //box
			break;
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
bool Raytrace::Trace(vector3 start, vector3 end, Physicsobject * physicsebject) {
	vector3 l;
	float a;
	float b;
	float c;
	float newt = 0;
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
	switch (physicsebject->shape) {
	case 0: //sphere
		a = end.dotProduct(end);
		/*vector3 bsqr = b * b; (start * start * end * end).multiply(4.0f);
		vector3 discriminant;*/
		/*discriminant = bsqr.Subtract(((start * start).Subtract(spherecolliders[i]->radius * spherecolliders[i]->radius) * a).multiply(4.0f));*/
		l = start - physicsebject->getPosition();
		b = 2.0f * end.dotProduct(l);
		c = l.dotProduct(l) - (physicsebject->getRadius() * physicsebject->getRadius());
		if (quadraticEquation(a, b, c, newt)) {
			t = newt;
			intersectionpoint = start + end.multiply(t);
			tracedobject = physicsebject;
			normal = intersectionpoint - physicsebject->getPosition();
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
		break;
	case 1: //box

	break;
	default:
	return false;
	}
}
bool Raytrace::Trace(vector3 start, vector3 end, vector3 position, float radius) {
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
	vector3 l = position - start;
	float tca = l.dotProduct(end);
	if (tca < 0) {
		t = -1;
		tracedobject = nullptr;
		normal = vector3(0.0, 0.0, 0.0);
		intersectionpoint = vector3(0.0, 0.0, 0.0);
		return false;
	}
	float d2 = l.dotProduct(l) - tca * tca;
	if (d2 > radius * radius) {
		t = -1;
		tracedobject = nullptr;
		normal = vector3(0.0, 0.0, 0.0);
		intersectionpoint = vector3(0.0, 0.0, 0.0);
		return false;
	}
	float thc = sqrt((radius * radius) - d2);
	float x0 = tca - thc;
	float x1 = tca + thc;
	if ((x0 < x1 || x1 < 0) && (x0 >= 0)) {
		t = x0;
	}
	else if ((x1 < x0 || x0 < 0) && (x1 >= 0)) {
		t = x1;
	}
	intersectionpoint = start + end.multiply(t);
	normal = intersectionpoint - position;
	normal = normal.Normalize();
	return true;
	/*vector3 l = start - position;
	float a = end.dotProduct(end);
	float b = 2.0f * end.dotProduct(l);
	float c = l.dotProduct(l) - radius;
	float newt = 0;
	if (quadraticEquation(a, b, c, newt)) {
		t = newt;
		intersectionpoint = start + end.multiply(t);
		tracedobject = nullptr;
		normal = intersectionpoint - position;
		normal = normal.Normalize();
		return true;
	}*/
	/*else {
		t = -1;
		tracedobject = nullptr;
		normal = vector3(0.0, 0.0, 0.0);
		intersectionpoint = vector3(0.0, 0.0, 0.0);
		return false;
	}*/
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
