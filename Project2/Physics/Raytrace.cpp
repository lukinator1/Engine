#include "Raytrace.h"


bool Raytrace::Trace(vector3 start, vector3 end) {
	vector3 l;
	float a = end.dotProduct(end);
	float b;
	float c;
	/*vector3 bsqr = b * b; (start * start * end * end).multiply(4.0f);
	vector3 discriminant;*/
	for (int i = 0; i < spherecolliders.size(); i++) {
		/*discriminant = bsqr.Subtract(((start * start).Subtract(spherecolliders[i]->radius * spherecolliders[i]->radius) * a).multiply(4.0f));*/
		l = start - spherecolliders[i]->collidertransform.position;
		b = 2.0f * end.dotProduct(l);
		c = l.dotProduct(l) - spherecolliders[i]->radius;
		if (!quadraticEquation(a, b, c)) {
			return false;
		}
		else {
			intersectionpoint = start + end.multiply(t);
			tracedobject = spherecolliders[i];
			normal = intersectionpoint - spherecolliders[i]->collidertransform.position;
			normal = normal.Normalize();
		}
	}
}

bool Raytrace::quadraticEquation(float &a, float &b, float &c) {
	float discrimenant = (b * b) - (4.0f  * a * c);
	if (discrimenant < 0) {  //no collision
		t = -1;
		tracedobject = nullptr;
		normal = vector3(0.0, 0.0, 0.0);
		intersectionpoint = vector3(0.0, 0.0, 0.0);
		return false;
	}
	else if (discrimenant > 0) { //collided on 2 points but only returning first
		float q = b >= 0 ? -0.5f * (b + sqrt(discrimenant)) : -0.5f * (b - sqrt(discrimenant));
		float x0 = q / a;
		float x1 = c / q;
		if (x0 < x1) {
			t = x0;
		}
		else {
			t = x1;
		}
		return true;
	}
	else {  //collided with 1
		t = -0.5f * b / a;
		return true;
	}
}

Raytrace::Raytrace()
{
}


Raytrace::~Raytrace()
{
}
