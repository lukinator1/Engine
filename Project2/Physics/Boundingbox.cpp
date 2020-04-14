#include "Boundingbox.h"
#include "../Global.h"
bool Boundingbox::Simulate(Physicsobject & otherobject) {
	bool collision = false;  //test for collisions here
	float collisiondistance = 0;
	vector3 sphere;
	float sqrdistance = 0;
	float x;
	float y;
	float z;
	switch (otherobject.shape) {
	case 0:						//sphere
		sphere = otherobject.getPosition();
		if (sphere.x < getMinextents().x) {
			sqrdistance += (sphere.x - getMinextents().x) * (sphere.x - getMinextents().x);
		}
		else if (sphere.x > getMaxextents().x) {
			sqrdistance += (sphere.x - getMaxextents().x) * (sphere.x - getMaxextents().x);
		}
		if (sphere.y < getMinextents().y) {
			sqrdistance += (sphere.y - getMinextents().y) * (sphere.y - getMinextents().y);
		}
		else if (sphere.y > getMaxextents().y) {
			sqrdistance += (sphere.y - getMaxextents().y) * (sphere.y - getMaxextents().y);
		}
		if (sphere.z < getMinextents().z) {
			sqrdistance += (sphere.z - getMinextents().z) * (sphere.z - getMinextents().z);
		}
		else if (sphere.z > getMaxextents().z) {
			sqrdistance += (sphere.z - getMaxextents().z) * (sphere.z - getMaxextents().z);
		}
			if (sqrdistance < (otherobject.getRadius() * otherobject.getRadius())) {  //test to see if collided, distance^2 < radius^2
				collision = true;
		}
	break;
	case 1:						//box
		vector3 difference = otherobject.getMinextents().Subtract(maxextents);
		vector3 otherdifference = minextents.Subtract(otherobject.getMaxextents());
		vector3 distance;
		if (difference.x >= otherdifference.x) {
			distance.x = difference.x;
		}
		else {
			distance.x = otherdifference.x;
		}
		if (difference.y >= otherdifference.y) {
			distance.y = difference.y;
		}
		else {
			distance.y = otherdifference.y;
		}
		if (difference.z >= otherdifference.z) {
			distance.z = difference.z;
		}
		else {
			distance.z = otherdifference.z;
		}
		float maxdistance = distance.x;
		collisiondistance = distance.x;
		if (distance.y >= maxdistance) {
			maxdistance = distance.y;
		}
		else {
			collisiondistance = distance.y;
		}
		if (distance.z >= maxdistance) {
			maxdistance = distance.z;
		}
		if (distance.z < collisiondistance) {
			collisiondistance = distance.z;
		}
		if (maxdistance < 0) {
			collision = true;;
		}
		break;
	}

	//collision occurred
	if (collision) {
		tempoldpos = oldpos;
		tempvel = velocity;
		collided = true;
		Raytrace ray;
		vector3 dir = oldpos - otherobject.oldpos;
		//ray.Trace(physicsobject.oldpos, dir, oldpos, radius);
		collisiondata.intersectionpoints.push_back(ray.intersectionpoint);
		collisiondata.intersectionnormals.push_back(ray.normal);
		//collisiondata.collisiondistance = collisiondistance;
		collisiondata.otherobjects.push_back(&otherobject);
		std::pair <float, vector3> momentum = { otherobject.mass, otherobject.velocity };
		collisiondata.momentia.push_back(momentum);
		collisiondata.forces.push_back(acceleration.multiply(mass));
	}
	return collision;
}
void Boundingbox::Integrate() {
	if (collided == true) {
		handleCollision();  //resolve forces/collisions
		collisiondata.intersectionpoints.clear();
		collisiondata.intersectionnormals.clear();
		collisiondata.collisiondistance = 0;
		collisiondata.otherobjects.clear();
		collisiondata.momentia.clear();
		collisiondata.forces.erase(collisiondata.forces.begin() + 1, collisiondata.forces.end());
	}
	oldpos = getPosition();
	vector3 newacceleration(acceleration.x, acceleration.y, acceleration.z);
	newacceleration = newacceleration.Subtract(gravity);
	Quaternion newangularvelocity(angularvelocity.x, angularvelocity.y, angularvelocity.z, 0);
	velocity = velocity.add(acceleration.multiply(deltatime));
	angularvelocity = angularvelocity.add(angularacceleration.multiply(deltatime));

	setPosition(getPosition() + (velocity.multiply(deltatime)).add(newacceleration.multiply((deltatime * deltatime) / 0.5f)));
	setRotation(getRotation() + (newangularvelocity.Multiply(getRotation()).Multiply(deltatime / 0.5f)));
}
void Boundingbox::handleConstraints()
{
	vector3 neg(1.0f, 1.0f, 1.0f);
	int sleep = 0;
	int count = 0;
	float factor = 1;
	bool done = false;
	std::pair<float, bool> collisiontester(0, false);
	float impulse = 0;
	vector3 term2;
	vector3 dir;
	Raytrace ray;
	while (!done && sleep <= 5) {
		done = true;
		for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
			collisiontester = calcCollision(*collisiondata.otherobjects[i]);//test if still colliding
			if (collisiontester.second == false) {
				continue;
			}
			else {
				done = false; 
			}

			neg = collisiondata.intersectionnormals[i];	//set to proper position
			setPosition(getPosition() - neg.multiply(collisiontester.first));

			count = 0; //if still didn't aren't separated
			factor = 1.0f;
			collisiontester = calcCollision(*collisiondata.otherobjects[i]);
			/*while ((collisiontester.second == true) && count < 60) {
				setPosition(getPosition() - neg.multiply(collisiontester.first /* factor));
				count++;

				if (count == 10) {
					//std::cout << "Constraint went to factor 2" << std::endl;
					factor = 2.65f;
				}
				else if (count == 20) {
					//std::cout << "Constraint went to factor 3" << std::endl;
					factor = 5.85f;
				}
				else if (count == 40) {
					//std::cout << "Constraint went to factor 4" << std::endl;
					factor = 6.5f;
				}
				collisiontester = calcCollision(*collisiondata.otherobjects[i]);
			}*/
		}
		sleep++;
		if (sleep == 5) {
			//std::cout << "Constraints handling went through max iterations";
		}
	}
}
void Boundingbox::handleCollision() {
	float momentiamass = 0;
	vector3 momentums;
	collisiondata.forces[0] = gravity;
	vector3 netforce = collisiondata.forces[0];
	vector3 nettorque;
	float angularimpulse = 0.1;
	float impulse = 0;
	vector3 t;
	float relvelnormal = 0;
	float testrelvel = 0;
	float sleep = 0;
	for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
		sleep = 0;
		/*momentums = momentums.add(collisiondata.momentia[i].second.multiply(collisiondata.momentia[i].first)); //impulse
		momentiamass += collisiondata.momentia[i].first;
		netforce += collisiondata.forces[i + 1];    //acceleration*/
		/*vector3 dir = tempoldpos - collisiondata.otherobjects[i]->tempoldpos;
		if (raytrace.Trace(collisiondata.otherobjects[i]->tempoldpos, dir, tempoldpos, radius)) {  //angle*/
		relvelnormal = (collisiondata.otherobjects[i]->tempvel - tempvel).dotProduct(collisiondata.intersectionnormals[i]);
		if (relvelnormal < 0) {
			testrelvel = -relvelnormal;
		}
		if (testrelvel < 0.01f) {
			sleep = elasticity;
		}

		impulse = -(1.0f + elasticity - sleep) * relvelnormal;
		vector3 rb = collisiondata.intersectionpoints[i] - tempoldpos;
		vector3 ra = collisiondata.intersectionpoints[i] - collisiondata.otherobjects[i]->tempoldpos;
		vector3 angimpa = (ra * collisiondata.intersectionnormals[i]).divide(collisiondata.otherobjects[i]->MOI) * (ra);
		vector3 angimpb = (rb * collisiondata.intersectionnormals[i]).divide(MOI) * rb;
		angularimpulse = (angimpa + angimpb).dotProduct(collisiondata.intersectionnormals[i]);
		impulse /= ((1.0f / collisiondata.otherobjects[i]->mass) + (1.0f / mass) + angularimpulse);

		t = ((collisiondata.intersectionnormals[i] * (collisiondata.otherobjects[i]->tempvel - tempvel)) * collisiondata.intersectionnormals[i]).Normalize();
		velocity = velocity - (collisiondata.intersectionnormals[i] + t.multiply(kineticfrictionconstant)).multiply((impulse / mass));
		angularvelocity = angularvelocity - (rb.crossProduct(((collisiondata.intersectionnormals[i] + t.multiply(kineticfrictionconstant)).multiply(impulse)))).divide(MOI);
		/*netforce += collisiondata.forces[i + 1];
		nettorque += (rb.crossProduct(collisiondata.forces[i + 1]));*/
	}
	/*netforce += acceleration.multiply(mass + 10.0f);
	acceleration += netforce.divide(momentiamass * elasticity + mass)
	angularacceleration += nettorque.divide(MOI);*/
}
std::pair<float, bool> Boundingbox::calcCollision(Physicsobject &phy) {  //returns collision distance and if it collided or not
	vector3 sphere;
	float distance = 0;

	vector3 boxdistance;
	vector3 difference;
	vector3 otherdifference;
	float maxdistance = 0;
	float collisiondistance = 0;
	std::pair<float, bool> returner(0, false);
	switch (phy.shape) {
		case 0: //sphere
		sphere = phy.getPosition();
			if (sphere.x < getMinextents().x) {
				distance += (sphere.x - getMinextents().x) * (sphere.x - getMinextents().x);
			}
			else if (sphere.x > getMaxextents().x) {
				distance += (sphere.x - getMaxextents().x) * (sphere.x - getMaxextents().x);
			}
			if (sphere.y < getMinextents().y) {
				distance += (sphere.y - getMinextents().y) * (sphere.y - getMinextents().y);
			}
			else if (sphere.y > getMaxextents().y) {
				distance += (sphere.y - getMaxextents().y) * (sphere.y - getMaxextents().y);
			}
			if (sphere.z < getMinextents().z) {
				distance += (sphere.z - getMinextents().z) * (sphere.z - getMinextents().z);
			}
			else if (sphere.z > getMaxextents().z) {
				distance += (sphere.z - getMaxextents().z) * (sphere.z - getMaxextents().z);
			}
			distance = sqrt(distance);
			returner.first = distance;
			if (distance < phy.getRadius()) {
				returner.second = false;
			}
			else {
				returner.second = true;
			}
			return returner;
		break;
		case 1: //AABB
			difference = phy.getMinextents().Subtract(maxextents);
			otherdifference = minextents.Subtract(phy.getMaxextents());
			if (difference.x >= otherdifference.x) {
				boxdistance.x = difference.x;
			}
			else {
				boxdistance.x = otherdifference.x;
			}
			if (difference.y >= otherdifference.y) {
				boxdistance.y = difference.y;
			}
			else {
				boxdistance.y = otherdifference.y;
			}
			if (difference.z >= otherdifference.z) {
				boxdistance.z = difference.z;
			}
			else {
				boxdistance.z = otherdifference.z;
			}
			maxdistance = boxdistance.x;
			collisiondistance = boxdistance.x;
			if (boxdistance.y >= maxdistance) {
				maxdistance = boxdistance.y;
			}
			else {
				collisiondistance = boxdistance.y;
			}
			if (boxdistance.z >= maxdistance) {
				maxdistance = boxdistance.z;
			}
			if (boxdistance.z < collisiondistance) {
				collisiondistance = boxdistance.z;
			}
			returner.first = collisiondistance;
			if (maxdistance < 0) {
				returner.second = true;
			}
			else {
				returner.second = false; 
			}
		break;
		default:
		return returner;
	}
	return returner;
}
void Boundingbox::recalculateMOI() {
	float s = (length + width + height) / 3.0f;
	MOI = (mass * s * s) / 6.0f;
}
void Boundingbox::setLength(float _length)
{
	length = _length;
	maxextents.z = getPosition().z + (length / 2.0f);
	minextents.z = getPosition().z - (length / 2.0f);
}
void Boundingbox::setWidth(float _width)
{
	width = _width;
	maxextents.x = getPosition().x + (width / 2.0f);
	minextents.x = getPosition().x - (width / 2.0f);
}
void Boundingbox::setHeight(float _height)
{
	height = _height;
	maxextents.y = getPosition().y + (height / 2.0f);
	minextents.y = getPosition().y - (height / 2.0f);
}
float Boundingbox::getLength()
{
	return length;
}
float Boundingbox::getWidth()
{
	return width;
}
float Boundingbox::getHeight()
{
	return height;
}
void Boundingbox::setColliderTransform(Transforming & t)
{
	collidertransform.position = t.position;
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
	minextents = vector3(getPosition().x - (width / 2.0f), getPosition().y - (length / 2.0f), getPosition().z - (length / 2.0f));
}
void Boundingbox::setPosition(vector3 pos)
{
	Physicsobject::setPosition(pos);
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
	minextents = vector3(getPosition().x - (width / 2.0f), getPosition().y - (length / 2.0f), getPosition().z - (length / 2.0f));
}
void Boundingbox::setPosition(float x, float y, float z)
{
	Physicsobject::setPosition(x, y, z);
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
	minextents = vector3(getPosition().x - (width / 2.0f), getPosition().y - (length / 2.0f), getPosition().z - (length / 2.0f));
}
/*void Boundingbox::setRotation(Quaternion rot)
{
	Physicsobject::setRotation(rot);
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
}*/
vector3 Boundingbox::getMinextents()
{
	return minextents;
}
vector3 Boundingbox::getMaxextents()
{
	return maxextents;
}
Boundingbox::Boundingbox()
{
	shape = 1;
	setLength(20.0f);
	setWidth(20.0f);
	setHeight(20.0f);
	float s = (length + width + height) / 3.0f;
	MOI = (mass * s * s)/6.0f;
}
Boundingbox::~Boundingbox()
{
}
