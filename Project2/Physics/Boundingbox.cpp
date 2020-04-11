#include "Boundingbox.h"
#include "../Global.h"
bool Boundingbox::Simulate(Physicsobject & otherobject) {
	bool collision = false;
	float collisiondistance = 0;
	float x;
	float y;
	float z;
	switch (otherobject.shape) {
	case 0:						//sphere
		x = std::max(minextents.x, std::min(otherobject.getPosition().x, maxextents.x));
		y = std::max(minextents.y, std::min(otherobject.getPosition().y, maxextents.y));
		z = std::max(minextents.z, std::min(otherobject.getPosition().z, maxextents.z));
		collisiondistance = sqrt((x - otherobject.getPosition().x) * (x - otherobject.getPosition().x) + (y - otherobject.getPosition().y) * (y - otherobject.getPosition().y) + (z - otherobject.getPosition().z) * (z - otherobject.getPosition().z));
		if (collisiondistance < otherobject.getRadius()) {
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

	if (collision) {
		tempoldpos = oldpos;
		tempvel = velocity;
		collided = true;
		Raytrace ray;
		vector3 dir = oldpos - otherobject.oldpos;
		//ray.Trace(physicsobject.oldpos, dir, oldpos, radius);
		collisiondata.intersectionpoints.push_back(ray.intersectionpoint);
		collisiondata.intersectionnormals.push_back(ray.normal);
		collisiondata.collisiondistance = collisiondistance;
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
		collided = false;
		collisiondata.intersectionpoints.clear();
		collisiondata.intersectionnormals.clear();
		collisiondata.collisiondistance = 0;
		collisiondata.otherobjects.clear();
		collisiondata.momentia.clear();
		collisiondata.forces.erase(collisiondata.forces.begin() + 1, collisiondata.forces.end());
	}
	oldpos = getPosition();
	vector3 newacceleration(acceleration.x, acceleration.y - gravity, acceleration.z);
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
	float collisiondistance = 0;
	float impulse = 0;
	vector3 term2;
	vector3 dir;
	Raytrace ray;
	while (!done && sleep != 7) {
		done = true;
		for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
			//collisiondistance = calcCollisionDistance(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->getPosition());//test if still colliding
			if (collisiondistance > 0) {
				done = false;
			}

			/*dir = collisiondata.otherobjects[i]->getPosition() - getPosition();
			if (!ray.Trace(getPosition(), dir, collisiondata.otherobjects[i])) {
				std::cout << "Ray didn't trace.";
			}*/
			neg = collisiondata.intersectionnormals[i];	//set to proper position

			/*setPosition(collisiondata.intersectionpoints[i] + neg.multiply(radius));*/

			count = 0; //if still didn't aren't separated
			factor = 1.65f;
			//collisiondistance = calcCollisionDistance(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->getPosition());
			while ((collisiondistance > 0) && count < 100) {
				/*velocity = velocity - (collisiondata.intersectionnormals[i]).multiply((50.0f / mass));*/
				setPosition(getPosition() - neg.multiply(collisiondistance * factor));
				count++;

				if (count == 10) {
					std::cout << "Constraint went to factor 2" << std::endl;
					factor = 2.75f;
				}
				else if (count == 20) {
					std::cout << "Constraint went to factor 3" << std::endl;
					factor = 3.85f;
				}
				else if (count == 40) {
					std::cout << "Constraint went to factor 4" << std::endl;
					factor = 4.5f;
				}
				//collisiondistance = calcCollisionDistance(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->getPosition());
			}
		}
		sleep++;
		if (sleep == 7) {
			std::cout << "Constraints handling went through max iterations";
		}
	}
}
void Boundingbox::handleCollision() {
	float momentiamass = 0;
	vector3 momentums;
	collisiondata.forces[0] = vector3(0, 0, gravity);
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
		/*}
		else {
			std::cout << "Something's probably broken." << std::endl;
		}*/
	}
	/*netforce += acceleration.multiply(mass + 10.0f);
	acceleration += netforce.divide(momentiamass * elasticity + mass)
	angularacceleration += nettorque.divide(MOI);*/
}
void Boundingbox::recalculateMOI() {
	float s = (length * width * height) / 3.0f;
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
	maxextents.y = getPosition().y + (length / 2.0f);
	minextents.y = getPosition().y - (length / 2.0f);
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
	Physicsobject::setColliderTransform(t);		//recalculate extents
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
}
void Boundingbox::setPosition(vector3 pos)
{
	Physicsobject::setPosition(pos);
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
}
void Boundingbox::setRotation(Quaternion rot)
{
	Physicsobject::setRotation(rot);
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
	maxextents = vector3(getPosition().x + (width / 2.0f), getPosition().y + (length / 2.0f), getPosition().z + (length / 2.0f));
}
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
	float s = (length * width * height) / 3.0f;
	MOI = (mass * s * s)/6.0f;
}
Boundingbox::~Boundingbox()
{
}
