#include "Boundingsphere.h"
#include "Raytrace.h"
#include "../Global.h"
/*bool Boundingsphere::Simulate(Boundingsphere &othersphere/*, float &collisiondistance){
	/loat radiusdistance = radius + othersphere.radius;
	float centerdistance = (othersphere.collidertransform.position.Subtract(collidertransform.position)).Magnitude();
	float collisiondistance = centerdistance - radiusdistance;
	if (centerdistance < radiusdistance) {
		collided = true;
		collisiondata.collisiondistance = collisiondistance;
		collisiondata.otherobjects.push_back(&othersphere);
		std::pair <float, vector3> momentum = { othersphere.mass, othersphere.velocity };
		collisiondata.momentia.push_back(momentum);
		collisiondata.forces.push_back(acceleration.multiply(mass));
		return true;
	}
	else {
		return false;
	}	
}*/
bool Boundingsphere::Simulate(Physicsobject &physicsobject)
{
	float radiusdistance;
	float centerdistance;
	//float collisiondistance = 0;
	bool collision = false;
	switch (physicsobject.shape) {			//test collisions
	case 0:													//sphere
		radiusdistance = radius + physicsobject.getRadius();
		centerdistance = (physicsobject.getPosition().Subtract(getPosition())).Magnitude();
		if (centerdistance < radiusdistance) {
			collision = true;
		}
		break;
	case 1:			//box
		vector3 sphere = getPosition();
		float sqrtdistance = 0;	
		if (sphere.x < physicsobject.getMinextents().x) {
			sqrtdistance += (sphere.x - physicsobject.getMinextents().x) * (sphere.x - physicsobject.getMinextents().x);
		}
		else if (sphere.x > physicsobject.getMaxextents().x) {
			sqrtdistance += (sphere.x - physicsobject.getMaxextents().x) * (sphere.x - physicsobject.getMaxextents().x);
		}
		if (sphere.y < physicsobject.getMinextents().y) {
			sqrtdistance += (sphere.y - physicsobject.getMinextents().y) * (sphere.y - physicsobject.getMinextents().y);
		}
		else if (sphere.y > physicsobject.getMaxextents().y) {
			sqrtdistance += (sphere.y - physicsobject.getMaxextents().y) * (sphere.y - physicsobject.getMaxextents().y);
		}
		if (sphere.z < physicsobject.getMinextents().z) {
			sqrtdistance += (sphere.z - physicsobject.getMinextents().z) * (sphere.z - physicsobject.getMinextents().z);
		}
		else if (sphere.z > physicsobject.getMaxextents().z) {
			sqrtdistance += (sphere.z - physicsobject.getMaxextents().z) * (sphere.z - physicsobject.getMaxextents().z);
		}

		if ((sqrtdistance) < (getRadius() * getRadius())) {
			collision = true;
		}
		break;
	}

	//collision succesful
	if (collision) {
			tempoldpos = oldpos;
			tempvel = velocity;
			collided = true;
			Raytrace ray;
			vector3 dir = oldpos - physicsobject.oldpos;
			ray.Trace(physicsobject.oldpos, dir, oldpos, radius);
			collisiondata.intersectionpoints.push_back(ray.intersectionpoint);
			collisiondata.intersectionnormals.push_back(ray.normal);
			//collisiondata.collisiondistance = collisiondistance;
			collisiondata.otherobjects.push_back(&physicsobject);
			std::pair <float, vector3> momentum = { physicsobject.mass, physicsobject.velocity };
			collisiondata.momentia.push_back(momentum);
			collisiondata.forces.push_back(acceleration.multiply(mass));
	}
	return collision;
}
void Boundingsphere::handleCollision() {
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
			impulse /= ( (1.0f / collisiondata.otherobjects[i]->mass) + (1.0f / mass) + angularimpulse);

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
void Boundingsphere::Integrate() {
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
bool Boundingsphere::intersectionTest(float _radius, vector3 _position, float &cdistance) {
	float radiusdistance = radius + _radius;
	float centerdistance = (_position.Subtract(getPosition())).Magnitude();
	cdistance = centerdistance - radiusdistance;
	if (centerdistance < radiusdistance) {
		return true;
	}
	else {
		return false;
	}
}
void Boundingsphere::handleConstraints()
{
	if (mass == INFINITY) {
		return;
	}
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
		while (!done && sleep != 5) {
			done = true;
			for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
				collisiontester = calcCollision(*collisiondata.otherobjects[i]); //test if still colliding
				if (collisiontester.second == false) {
					continue;
				}
				else {
					done = false;
				}

				neg = collisiondata.intersectionnormals[i];	//set to proper position
				setPosition(getPosition() - neg.multiply(collisiontester.first));

				count = 0; //if still didn't aren't separated
				factor = 1.2;
				collisiontester = calcCollision(*collisiondata.otherobjects[i]);
				while ((collisiontester.second == true) && count < 50) {
					setPosition(getPosition() - neg.multiply(collisiontester.first * factor));
					count++;

					if (count == 10) {
						//std::cout << "Constraint went to factor 2" << std::endl;
						factor = 2.0f;
					}
					else if (count == 20) {
						//std::cout << "Constraint went to factor 3" << std::endl;
						factor = 2.5;
					}
					else if (count == 40) {
						//std::cout << "Constraint went to factor 4" << std::endl;
						factor = 7.0f;
					}
					collisiontester = calcCollision(*collisiondata.otherobjects[i]);
				}
			}
			sleep++;
			if (sleep == 5) {
				//std::cout << "Constraints handling went through max iterations";
			}
	}
}
std::pair<float, bool> Boundingsphere::calcCollision(Physicsobject &phy) {
	std::pair<float, bool> returner(0, false);
	float radiusdistance = 0;
	float centerdistance = 0;
	float collisiondistance = 0;

	vector3 sphere;
	float spheredistance = 0;
	switch (phy.shape) {
	case 0:
		radiusdistance = radius + phy.getRadius();
		centerdistance = (phy.getPosition().Subtract(getPosition())).Magnitude();
		collisiondistance = -(centerdistance - radiusdistance);
		returner.first = collisiondistance;
		if (centerdistance < radiusdistance) {
			returner.second = true;
		}
		else {
			returner.second = false;
		}
		break;
	case 1:
		sphere = getPosition();
		if (sphere.x < phy.getMinextents().x) {
			spheredistance += (sphere.x - phy.getMinextents().x) * (sphere.x - phy.getMinextents().x);
		}
		else if (sphere.x > phy.getMaxextents().x) {
			spheredistance += (sphere.x - phy.getMaxextents().x) * (sphere.x - phy.getMaxextents().x);
		}
		if (sphere.y < phy.getMinextents().y) {
			spheredistance += (sphere.y - phy.getMinextents().y) * (sphere.y - phy.getMinextents().y);
		}
		else if (sphere.y > phy.getMaxextents().y) {
			spheredistance += (sphere.y - phy.getMaxextents().y) * (sphere.y - phy.getMaxextents().y);
		}
		if (sphere.z < phy.getMinextents().z) {
			spheredistance += (sphere.z - phy.getMinextents().z) * (sphere.z - phy.getMinextents().z);
		}
		else if (sphere.z > phy.getMaxextents().z) {
			spheredistance += (sphere.z - phy.getMaxextents().z) * (sphere.z - phy.getMaxextents().z);
		}
		spheredistance = sqrt(spheredistance);
		returner.first = spheredistance;

		if ((spheredistance) < (getRadius() * getRadius())) {
			returner.second = true;
		}
		break;
	default: 
		return returner;
	}
	return returner;
}
void Boundingsphere::recalculateMOI() {
	MOI = (2.0f / 5.0f) * mass * radius * radius;
}
float Boundingsphere::getRadius()
{
	return radius;
}
Boundingsphere::Boundingsphere()
{
	radius = 20.0f;
	MOI = (2.0f / 5.0f) * mass * radius * radius;
	shape = 0;
}
Boundingsphere::~Boundingsphere()
{
}
