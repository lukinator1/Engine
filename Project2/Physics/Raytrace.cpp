#include "Raytrace.h"
std::vector<Raytrace> Raytrace::Trace(vector3 start, vector3 end) { //end is actually direction
	t = -1;  //error return values because return will be in array
	tracedobject = nullptr;
	normal = vector3(0, 0, 0);
	intersectionpoint = start;
	std::vector<Raytrace> raytraces;
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
	vector3 l;
	float a = end.dotProduct(end);
	float b;
	float c;
	float newt = 0;
	for (int i = 0; i < colliders.size(); i++) {
		switch (colliders[i]->shape) {
		case 0: //sphere
			l = start - colliders[i]->getPosition();
			b = 2.0f * end.dotProduct(l);
			c = l.dotProduct(l) - (colliders[i]->getRadius() * colliders[i]->getRadius());
			if (quadraticEquation(a, b, c, newt)) {
				t = newt;
				raytraces.push_back(Raytrace());
				raytraces.back().intersectionpoint = start + end.multiply(t);
				raytraces.back().tracedobject = colliders[i];
				raytraces.back().normal = (intersectionpoint - colliders[i]->getPosition()).Normalize();
			}
			break;
		case 1: //box
			float tfinal;
			float tmin;
			float tmax;
			float tymin;
			float tymax;
			if (end.x > 0) {
				tmin = (colliders[i]->getMinextents().x - start.x) / end.x;
				tmax = (colliders[i]->getMaxextents().x - start.x) / end.x;
			}
			else if (end.x < 0) {
				tmin = (colliders[i]->getMaxextents().x - start.x) / end.x;
				tmax = (colliders[i]->getMinextents().x - start.x) / end.x;
			}
			else {
				tmin = INFINITY;
				tmax = INFINITY;
			}
			if (end.y > 0) {
				tymin = (colliders[i]->getMinextents().y - start.y) / end.y;
				tymax = (colliders[i]->getMaxextents().y - start.y) / end.y;
			}
			else if (end.y < 0) {
				tymin = (colliders[i]->getMaxextents().y - start.y) / end.y;
				tymax = (colliders[i]->getMinextents().y - start.y) / end.y;
			}
			else {
				tymin = INFINITY;
				tymax = INFINITY;
			}

			if ((tmin > tymax) || (tymin > tmax)) {
				continue;
			}
			if (tymin > tmin) {
				tmin = tymin;
			}
			if (tymax < tmax) {
				tmax = tymax;
			}

			float tzmin;
			float tzmax;

			if (end.z > 0) {
				tzmin = (colliders[i]->getMinextents().z - start.z) / end.z;
				tzmax = (colliders[i]->getMaxextents().z - start.z) / end.z;
			}
			else if (end.z < 0) {
				tzmin = (colliders[i]->getMaxextents().z - start.y) / end.z;
				tzmax = (colliders[i]->getMinextents().z - start.z) / end.z;
			}
			else {
				tzmin = INFINITY;
				tzmax = INFINITY;
			}

			if ((tmin > tzmax) || (tzmin > tmax)) {
				continue;
			}
			if (tzmin > tmin) {
				tmin = tzmin;
			}
			if (tzmax < tmax) {
				tmax = tzmax;
			}
		
			if ((tmin < tmax || tmax < 0) && (tmin >= 0)) {
				tfinal = tmin;
			}
			else if ((tmax < tmin || tmin < 0) && (tmax >= 0)) {
				tfinal = tmax;
			}
			if (tfinal == INFINITY){
				tfinal = 0;
			}
			raytraces.push_back(Raytrace());
			raytraces.back().t = tfinal;
			raytraces.back().intersectionpoint = start + end.multiply(tfinal);
			raytraces.back().tracedobject = colliders[i];
			raytraces.back().normal = (intersectionpoint - colliders[i]->getPosition()).Normalize();
			break;
		}
	}

	bool swapped = false;
	while (swapped == false) {
		swapped = true;
		for (int i = 0; i < raytraces.size() - 1; i++) {  //sort them when you're done
			if (raytraces[i].t > raytraces[i + 1].t) {
				std::swap(raytraces[i], raytraces[i + 1]);
				swapped = false;
			}
		}
	}
	return raytraces;
}
std::vector<Raytrace> Raytrace::Trace(vector3 start, vector3 end, std::vector<Physicsobject *> ignore) { //end is actually direction
	t = -1;  //error return values because return will be in array
	tracedobject = nullptr;
	normal = vector3(0, 0, 0);
	intersectionpoint = start;
	std::vector<Raytrace> raytraces;
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
	vector3 l;
	float a = end.dotProduct(end);
	float b;
	float c;
	float newt = 0;
	bool traced = false;
	bool ig = false; 
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
					t = newt;
					raytraces.push_back(Raytrace());
					raytraces.back().intersectionpoint = start + end.multiply(t);
					raytraces.back().tracedobject = colliders[i];
					raytraces.back().normal = (intersectionpoint - colliders[i]->getPosition()).Normalize();
			}
			break;
		case 1: //box
			float tfinal;
			float tmin;
			float tmax;
			float tymin;
			float tymax;
			if (end.x > 0) {
				tmin = (colliders[i]->getMinextents().x - start.x) / end.x;
				tmax = (colliders[i]->getMaxextents().x - start.x) / end.x;
			}
			else if (end.x < 0) {
				tmin = (colliders[i]->getMaxextents().x - start.x) / end.x;
				tmax = (colliders[i]->getMinextents().x - start.x) / end.x;
			}
			else {
				tmin = INFINITY;
				tmax = INFINITY;
			}
			if (end.y > 0) {
				tymin = (colliders[i]->getMinextents().y - start.y) / end.y;
				tymax = (colliders[i]->getMaxextents().y - start.y) / end.y;
			}
			else if (end.y < 0) {
				tymin = (colliders[i]->getMaxextents().y - start.y) / end.y;
				tymax = (colliders[i]->getMinextents().y - start.y) / end.y;
			}
			else {
				tymin = INFINITY;
				tymax = INFINITY;
			}

			if ((tmin > tymax) || (tymin > tmax)) {
				continue;
			}
			if (tymin > tmin) {
				tmin = tymin;
			}
			if (tymax < tmax) {
				tmax = tymax;
			}

			float tzmin;
			float tzmax;

			if (end.z > 0) {
				tzmin = (colliders[i]->getMinextents().z - start.z) / end.z;
				tzmax = (colliders[i]->getMaxextents().z - start.z) / end.z;
			}
			else if (end.z < 0) {
				tzmin = (colliders[i]->getMaxextents().z - start.y) / end.z;
				tzmax = (colliders[i]->getMinextents().z - start.z) / end.z;
			}
			else {
				tzmin = INFINITY;
				tzmax = INFINITY;
			}

			if ((tmin > tzmax) || (tzmin > tmax)) {
				continue;
			}
			if (tzmin > tmin) {
				tmin = tzmin;
			}
			if (tzmax < tmax) {
				tmax = tzmax;
			}

			if ((tmin < tmax || tmax < 0) && (tmin >= 0)) {
				tfinal = tmin;
			}
			else if ((tmax < tmin || tmin < 0) && (tmax >= 0)) {
				tfinal = tmax;
			}
			if (tfinal == INFINITY) {
				tfinal = 0;
			}
			raytraces.push_back(Raytrace());
			raytraces.back().t = tfinal;
			raytraces.back().intersectionpoint = start + end.multiply(tfinal);
			raytraces.back().tracedobject = colliders[i];
			raytraces.back().normal = (intersectionpoint - colliders[i]->getPosition()).Normalize();
			break;
		}
	}
	bool swapped = false;
	while (swapped == false) {
		swapped = true;
		for (int i = 0; i < raytraces.size() - 1; i++) {  //sort them when you're done
			if (raytraces[i].t > raytraces[i + 1].t) {
				std::swap(raytraces[i], raytraces[i + 1]);
				swapped = false;
			}
		}
	}
	return raytraces;
}
bool Raytrace::Trace(vector3 start, vector3 end, Physicsobject * physicsebject) {
	t = -1;
	tracedobject = nullptr;
	normal = vector3(0.0, 0.0, 0.0);
	intersectionpoint = start;
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
			return false;
		}
		break;
	case 1: //box
		float tfinal;
		float tmin;
		float tmax;
		float tymin;
		float tymax;
		if (end.x > 0) {
			tmin = (physicsebject->getMinextents().x - start.x) / end.x;
			tmax = (physicsebject->getMaxextents().x - start.x) / end.x;
		}
		else if (end.x < 0) {
			tmin = (physicsebject->getMaxextents().x - start.x) / end.x;
			tmax = (physicsebject->getMinextents().x - start.x) / end.x;
		}
		else {
			tmin = INFINITY;
			tmax = INFINITY;
		}
		if (end.y > 0) {
			tymin = (physicsebject->getMinextents().y - start.y) / end.y;
			tymax = (physicsebject->getMaxextents().y - start.y) / end.y;
		}
		else if (end.y < 0) {
			tymin = (physicsebject->getMaxextents().y - start.y) / end.y;
			tymax = (physicsebject->getMinextents().y - start.y) / end.y;
		}
		else {
			tymin = INFINITY;
			tymax = INFINITY;
		}

		if ((tmin > tymax) || (tymin > tmax)) {
			return false;
		}
		if (tymin > tmin) {
			tmin = tymin;
		}
		if (tymax < tmax) {
			tmax = tymax;
		}

		float tzmin;
		float tzmax;

		if (end.z > 0) {
			tzmin = (physicsebject->getMinextents().z - start.z) / end.z;
			tzmax = (physicsebject->getMaxextents().z - start.z) / end.z;
		}
		else if (end.z < 0) {
			tzmin = (physicsebject ->getMaxextents().z - start.y) / end.z;
			tzmax = (physicsebject->getMinextents().z - start.z) / end.z;
		}
		else {
			tzmin = INFINITY;
			tzmax = INFINITY;
		}

		if ((tmin > tzmax) || (tzmin > tmax)) {
			return false;
		}
		if (tzmin > tmin) {
			tmin = tzmin;
		}
		if (tzmax < tmax) {
			tmax = tzmax;
		}

		if ((tmin < tmax || tmax < 0) && (tmin >= 0)) {
			tfinal = tmin;
		}
		else if ((tmax < tmin || tmin < 0) && (tmax >= 0)) {
			tfinal = tmax;
		}
		t = tfinal;
		if (t == INFINITY) {
			t = 0;
		}
		intersectionpoint = start + end.multiply(t);
		tracedobject = physicsebject;
		normal = (intersectionpoint - physicsebject->getPosition()).Normalize();
		return true;
	break;
	default:
	return false;
	}
}
bool Raytrace::Trace(vector3 start, vector3 end, vector3 position, float radius) { //ray->sphere
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
}
bool Raytrace::Trace(vector3 start, vector3 end, vector3 position, float length, float width, float height) { //ray->box
	vector3 maxextents = vector3(position.x + (width / 2.0f), position.z + (length / 2.0f), position.y + (height / 2.0f));
	vector3 minextents = vector3(position.x - (width / 2.0f), position.z - (length / 2.0f), position.y - (height / 2.0f));
	t = -1;
	tracedobject = nullptr;
	normal = vector3(0.0, 0.0, 0.0);
	intersectionpoint = start;
	vector3 l;
	float a;
	float b;
	float c;
	float newt = 0;
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
		float tfinal;
		float tmin;
		float tmax;
		float tymin;
		float tymax;
		if (end.x > 0) {
			tmin = (minextents.x - start.x) / end.x;
			tmax = (maxextents.x - start.x) / end.x;
		}
		else if (end.x < 0) {
			tmin = (maxextents.x - start.x) / end.x;
			tmax = (minextents.x - start.x) / end.x;
		}
		else {
			tmin = INFINITY;
			tmax = INFINITY;
		}
		if (end.y > 0) {
			tymin = (minextents.y - start.y) / end.y;
			tymax = (maxextents.y - start.y) / end.y;
		}
		else if (end.y < 0) {
			tymin = (maxextents.y - start.y) / end.y;
			tymax = (minextents.y- start.y) / end.y;
		}
		else {
			tymin = INFINITY;
			tymax = INFINITY;
		}

		if ((tmin > tymax) || (tymin > tmax)) {
			return false;
		}
		if (tymin > tmin) {
			tmin = tymin;
		}
		if (tymax < tmax) {
			tmax = tymax;
		}

		float tzmin;
		float tzmax;

		if (end.z > 0) {
			tzmin = (minextents.z - start.z) / end.z;
			tzmax = (maxextents.z - start.z) / end.z;
		}
		else if (end.z < 0) {
			tzmin = (maxextents.z - start.y) / end.z;
			tzmax = (minextents.z - start.z) / end.z;
		}
		else {
			tzmin = INFINITY;
			tzmax = INFINITY;
		}

		if ((tmin > tzmax) || (tzmin > tmax)) {
			return false;
		}
		if (tzmin > tmin) {
			tmin = tzmin;
		}
		if (tzmax < tmax) {
			tmax = tzmax;
		}

		if ((tmin < tmax || tmax < 0) && (tmin >= 0)) {
			tfinal = tmin;
		}
		else if ((tmax < tmin || tmin < 0) && (tmax >= 0)) {
			tfinal = tmax;
		}
		t = tfinal;
		if (t == INFINITY) {
			t = 0;
		}
		intersectionpoint = start + end.multiply(t);
		normal = (intersectionpoint - position).Normalize();
		return true;
}
bool Raytrace::Trace(vector3 start, vector3 end, vector3 position, vector3 maxextents, vector3 minextents) { //ray->box, max/minextents
	t = -1;
	tracedobject = nullptr;
	normal = vector3(0.0, 0.0, 0.0);
	intersectionpoint = start;
	if (end.Magnitude() != 1) {
		end = end.Normalize();
	}
	vector3 invdirec(1.0f / end.x, 1.0f / end.y, 1.0f / end.z);
	float tfinal;
	float tmin;
	float tmax;
	float tymin;
	float tymax;
	if (invdirec.x >= 0) {
		tmin = (minextents.x - start.x) * invdirec.x;
		tmax = (maxextents.x - start.x)  * invdirec.x;
	}
	else if (invdirec.x < 0) {
		tmin = (maxextents.x - start.x) * invdirec.x;
		tmax = (minextents.x - start.x) * invdirec.x;
	}
	else {
		tmin = INFINITY;
		tmax = INFINITY;
	}
	if (invdirec.y >= 0) {
		tymin = (minextents.y - start.y) * invdirec.y;
		tymax = (maxextents.y - start.y) * invdirec.y;
	}
	else if (invdirec.y < 0) {
		tymin = (maxextents.y - start.y) * invdirec.y;
		tymax = (minextents.y - start.y) * invdirec.y;
	}
	else {
		tymin = INFINITY;
		tymax = INFINITY;
	}

	if ((tmin > tymax) || (tymin > tmax)) {
		return false;
	}
	if (tymin > tmin) {
		tmin = tymin;
	}
	if (tymax < tmax) {
		tmax = tymax;
	}

	float tzmin;
	float tzmax;

	if (invdirec.z >= 0) {
		tzmin = (minextents.z - start.z) * invdirec.z;
		tzmax = (maxextents.z - start.z) * invdirec.z;
	}
	else if (invdirec.z < 0) {
		tzmin = (maxextents.z - start.z) * invdirec.z;
		tzmax = (minextents.z - start.z) * invdirec.z;
	}
	else {
		tzmin = INFINITY;
		tzmax = INFINITY;
	}

	if ((tmin > tzmax) || (tzmin > tmax)) {
		return false;
	}
	if (tzmin > tmin) {
		tmin = tzmin;
	}
	if (tzmax < tmax) {
		tmax = tzmax;
	}

	/*if (tmax <= tmin) {
		if (tmax >= 0) {
			tfinal = tmax;
		}
		else {
			return false;
		}
	}
	else if (tmin <= tmax) {
		if (tmin >= 0) {
			tfinal = tmin;
		}
		else {
			return false;
		}
	}*/
	if ((tmin < tmax || tmax < 0) && (tmin >= 0)) {
		tfinal = tmin;
	}
	else if ((tmax < tmin || tmin < 0) && (tmax >= 0)) {
		tfinal = tmax;
	}

	t = tfinal;
	if (t == INFINITY) {
		t = 0;
	}
	intersectionpoint = start + end.multiply(t);
	normal = (intersectionpoint - position).Normalize();
	return true;
}
bool Raytrace::quadraticEquation(float &a, float &b, float &c, float &t) {
	float discrimenant = (b * b) - (4.0f  * a * c);
	if (discrimenant < 0) {  //no collision
		return false;
	}
	else if (discrimenant > 0) { //collided on 2 points but only returning first
		float q = (b > 0) ? -0.5f * (b + sqrt(discrimenant)) : -0.5f * (b - sqrt(discrimenant));
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
			return x0;
		}
	}
	else {  //collided with 1
		float q = -0.5f * b / a;
		if (q >= 0) {
			t = q;
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
