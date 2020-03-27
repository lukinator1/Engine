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
		collisiondistance = centerdistance - radiusdistance;
		if (centerdistance < radiusdistance) {
			collided = true;
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
	Raytrace raytrace;
	for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
		/*momentums = momentums.add(collisiondata.momentia[i].second.multiply(collisiondata.momentia[i].first)); //impulse
		momentiamass += collisiondata.momentia[i].first;
		netforce += collisiondata.forces[i + 1];    //acceleration*/

		vector3 dir = tempoldpos - collisiondata.otherobjects[i]->tempoldpos;
		if (raytrace.Trace(collisiondata.otherobjects[i]->tempoldpos, dir, tempoldpos, radius)) {  //angle
			impulse = -(1.0f + elasticity);
			impulse *= (collisiondata.otherobjects[i]->tempvel - tempvel).dotProduct(raytrace.normal);
			vector3 rb = raytrace.intersectionpoint - tempoldpos;
			vector3 ra = raytrace.intersectionpoint - collisiondata.otherobjects[i]->tempoldpos;
			vector3 angimpa = (ra * raytrace.normal).divide(collisiondata.otherobjects[i]->MOI) * (ra);
			vector3 angimpb = (rb * raytrace.normal).divide(MOI) * rb;
			angularimpulse = (angimpa + angimpb).dotProduct(raytrace.normal);
			impulse /= ( (1.0f / collisiondata.otherobjects[i]->mass) + (1.0f / mass) + angularimpulse);

			t = (raytrace.normal * (collisiondata.otherobjects[i]->tempvel.Normalize() - tempvel.Normalize())) * raytrace.normal;
			velocity = velocity - (raytrace.normal + t.multiply(kineticfrictionconstant)).multiply((impulse / mass));
			angularvelocity = angularvelocity - (rb * ((raytrace.normal + t.multiply(kineticfrictionconstant)).multiply(impulse))).divide(MOI);
			/*netforce += collisiondata.forces[i + 1];
			nettorque += (rb.crossProduct(collisiondata.forces[i + 1]));*/
		}
		else {
			std::cout << "Something's probably broken." << std::endl;
		}
	}
	/*netforce += acceleration.multiply(mass + 10.0f);
	acceleration += netforce.divide(momentiamass * elasticity + mass)
	angularacceleration += nettorque.divide(MOI);*/
}
void Boundingsphere::Integrate() {
	if (collided == true) {
		tempoldpos = oldpos;
		tempvel = velocity;
		handleCollision();  //resolve forces/collisions
	}
	oldpos = getPosition();
	vector3 newacceleration(acceleration.x, acceleration.y - gravity, acceleration.z);
	Quaternion newangularvelocity(angularvelocity.x, angularvelocity.y, angularvelocity.z, 0);
	velocity = velocity.add(acceleration.multiply(deltatime));
	angularvelocity = angularvelocity.add(angularacceleration.multiply(deltatime));

	setPosition( getPosition() + (velocity.multiply(deltatime)).add(newacceleration.multiply((deltatime * deltatime) / 0.5f)));
	/*collidertransform.rotation = collidertransform.rotation.Add(newangularvelocity.Multiply(collidertransform.rotation));
	boundingsphere.collidertransform.Rotate(boundingsphere.angularvelocity.multiply(deltatime).add(boundingsphere.angularacceleration.multiply((deltatime * deltatime) / 0.5f)));*/
	setRotation(getRotation() + (newangularvelocity.Multiply(getRotation()).Multiply(deltatime / 0.5f)));
}
bool Boundingsphere::intersectionTest(float _radius, vector3 _position) {
	float radiusdistance = radius + _radius;
	float centerdistance = (_position.Subtract(getPosition())).Magnitude();
	float collisiondistance = centerdistance - radiusdistance;
	if (centerdistance < radiusdistance) {
		return true;
	}
	else {
		return false;
	}
}
void Boundingsphere::handleConstraints()
{
	vector3 neg(1.0f, 1.0f, 1.0f);
	int sleep = 0;
	int count = 0;
	bool done = false;
	while (!done || sleep == 15) {
		done = true;
		for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
			neg = collisiondata.otherobjects[i]->getPosition().negateVector();
			neg = neg.Normalize();
			while (intersectionTest(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->getPosition())) {
				setPosition(getPosition() + neg.multiply(collisiondata.collisiondistance));
				count++;
				if (count > 1) {

				}
				done = false;
			}
			sleep++;
		}
	}
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
