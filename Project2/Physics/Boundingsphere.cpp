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
	float collisiondistance;
	switch (physicsobject.shape) {
	case 0:													//sphere
		radiusdistance = radius + physicsobject.getRadius();
		centerdistance = (physicsobject.getPosition().Subtract(getPosition())).Magnitude();
		collisiondistance = -(centerdistance - radiusdistance);
		if (centerdistance < radiusdistance) {
			tempoldpos = oldpos;
			tempvel = velocity;
			collided = true;
			Raytrace ray;
			vector3 dir = oldpos - physicsobject.oldpos;
			ray.Trace(physicsobject.oldpos, dir, oldpos, radius);
			collisiondata.intersectionpoints.push_back(ray.intersectionpoint);
			collisiondata.intersectionnormals.push_back(ray.normal);
			collisiondata.collisiondistance = collisiondistance;
			collisiondata.otherobjects.push_back(&physicsobject);
			std::pair <float, vector3> momentum = { physicsobject.mass, physicsobject.velocity };
			collisiondata.momentia.push_back(momentum);
			collisiondata.forces.push_back(acceleration.multiply(mass));
			return true;
		}
		else {
			return false;
		}
		break;
	case 1:													//box
		break;
	}
	return false;
}
void Boundingsphere::handleCollision() {
	float momentiamass = 0;
	vector3 momentums;
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
			else {
				int x = 0;
			}
			impulse = -(1.0f + elasticity - sleep) * relvelnormal;
			vector3 rb = collisiondata.intersectionpoints[i] - tempoldpos;
			vector3 ra = collisiondata.intersectionpoints[i] - collisiondata.otherobjects[i]->tempoldpos;
			vector3 angimpa = (ra * collisiondata.intersectionnormals[i]).divide(collisiondata.otherobjects[i]->MOI) * (ra);
			vector3 angimpb = (rb * collisiondata.intersectionnormals[i]).divide(MOI) * rb;
			angularimpulse = (angimpa + angimpb).dotProduct(collisiondata.intersectionnormals[i]);
			impulse /= ( (1.0f / collisiondata.otherobjects[i]->mass) + (1.0f / mass) + angularimpulse);

			t = (collisiondata.intersectionnormals[i] * (collisiondata.otherobjects[i]->tempvel.Normalize() - tempvel.Normalize())) * collisiondata.intersectionnormals[i];
			velocity = velocity - (collisiondata.intersectionnormals[i] + t.multiply(kineticfrictionconstant)).multiply((impulse / mass));
			angularvelocity = angularvelocity - (rb * ((collisiondata.intersectionnormals[i] + t.multiply(kineticfrictionconstant)).multiply(impulse))).divide(MOI);
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
void Boundingsphere::Integrate() {
	if (collided == true) {
		/*tempoldpos = oldpos;
		tempvel = velocity;*/
		handleCollision();  //resolve forces/collisions
	}
	oldpos = getPosition();
	vector3 newacceleration(acceleration.x, acceleration.y - gravity, acceleration.z);
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
float Boundingsphere::calcCollisionDistance(float _radius, vector3 _position) {
	float radiusdistance = radius + _radius;
	float centerdistance = (_position.Subtract(getPosition())).Magnitude();
	float collisiondistance = -(centerdistance - radiusdistance);
	return collisiondistance;
}
void Boundingsphere::handleConstraints()
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
	/*while (!done && sleep != 7) {
		done = true;
		for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
			collisiondistance = calcCollisionDistance(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->getPosition());
			if (collisiondistance > 0) {
			dir = collisiondata.otherobjects[i]->getPosition() - collisiondata.otherobjects[i]->oldpos;
			ray.Trace(collisiondata.otherobjects[i]->getPosition(), dir, collisiondata.otherobjects[i]->oldpos, collisiondata.otherobjects[i]->getRadius());
			erm2 = velocity + angularvelocity.multiply(collisiondata[i])
		}
	}*/
	/*while (!done && sleep != 7) {
		done = true;
		for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
			count = 0;
			dir = collisiondata.otherobjects[i]->getPosition() - getPosition();
			if (!ray.Trace(getPosition(), dir, collisiondata.otherobjects[i])) {
				std::cout << "Ray didn't trace.";
			}
			neg = (ray.normal).Normalize();
			while (intersectionTest(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->getPosition()) && count < 100) {
				setPosition(getPosition() + neg.multiply(collisiondata.collisiondistance));
				count++;
				if (count == 100) {
					std::cout << "Constraint is taking too long, object may still be colliding.";
				}
				done = false;
			}
			sleep++;
			if (sleep == 7) {
				std::cout << "Constraint went through max iterations";
			}
		}
	}*/
		while (!done && sleep != 7) {
			done = true;
			for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
				collisiondistance = calcCollisionDistance(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->getPosition());//test if still colliding
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
				factor = 1;
				collisiondistance = calcCollisionDistance(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->getPosition());
				while ((collisiondistance >0) && count < 100) {
					/*velocity = velocity - (collisiondata.intersectionnormals[i]).multiply((50.0f / mass));*/
					setPosition(getPosition() - neg.multiply(collisiondistance * factor));
					count++;

					if (count == 10) {
						std::cout << "Constraint went to factor 2" << std::endl;
						factor = 2;
					}
					else if (count == 20) {
						std::cout << "Constraint went to factor 3" << std::endl;
						factor = 3;
					}
					else if (count == 40) {
						std::cout << "Constraint went to factor 4" << std::endl;
						factor = 4;
					}
					collisiondistance = calcCollisionDistance(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->getPosition());
				}
			}
			sleep++;
			if (sleep == 7) {
				std::cout << "Constraints handling went through max iterations";
			}
	}
	/*while (!done || sleep == 7) {
		done = true;
		for (int i = 0; i < colliders.size(); i++) {
			if (this != colliders[i]) {
				continue;
			}
			count = 0;
			dir = colliders[i]->getPosition() - getPosition();
			if (!ray.Trace(getPosition(), dir, colliders[i])) {
				/*std::cout << "Ray didn't trace.";
			}
			neg = (ray.normal).Normalize();

			collisiondistance = intersectionTest(colliders[i]->getRadius(), colliders[i]->getPosition());
			if (collisiondistance < 0) {
				done = false;
			}
			while ((collisiondistance < 0) && count < 100) {
				setPosition(getPosition() + neg.multiply(collisiondistance));
				count++;
				if (count == 100) {
					std::cout << "Constraint is taking too long, object may still be colliding.";
				}
			}
		}
		sleep++;
		if (sleep == 7) {
			std::cout << "Constraint went through max iterations";
		}
	}*/
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
