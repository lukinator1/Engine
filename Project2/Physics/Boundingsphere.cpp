#include "Boundingsphere.h"
#include "Raytrace.h"
#include "../Global.h"
bool Boundingsphere::Simulate(Boundingsphere &othersphere/*, float &collisiondistance*/){
	float radiusdistance = radius + othersphere.radius;
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
}
bool Boundingsphere::intersectionTest(float _radius, vector3 _position) {
	float radiusdistance = radius + _radius;
	float centerdistance = (_position.Subtract(collidertransform.position)).Magnitude();
	float collisiondistance = centerdistance - radiusdistance;
	if (centerdistance < radiusdistance) {
		return true;
	}
	else {
		return false;
	}
}

void Boundingsphere::Simulate(Physicsobject physicsobject)
{
}
void Boundingsphere::Integrate() {
	if (collided == true) {
		tempoldpos = oldpos;
		tempvel = velocity;
		handleCollision();  //resolve forces/collisions
	}
	oldpos = collidertransform.position;
	vector3 newacceleration(acceleration.x, acceleration.y - gravity, acceleration.z);
	Quaternion newangularvelocity(angularvelocity.x, angularvelocity.y, angularvelocity.z, 0);
	velocity = velocity.add(acceleration.multiply(deltatime));
	angularvelocity = angularvelocity.add(angularacceleration.multiply(deltatime));

	collidertransform.position = collidertransform.position.add(velocity.multiply(deltatime)).add(newacceleration.multiply((deltatime * deltatime) / 0.5f));
	/*collidertransform.rotation = collidertransform.rotation.Add(newangularvelocity.Multiply(collidertransform.rotation));
	boundingsphere.collidertransform.Rotate(boundingsphere.angularvelocity.multiply(deltatime).add(boundingsphere.angularacceleration.multiply((deltatime * deltatime) / 0.5f)));
	boundingsphere.collidertransform.rotation = boundingsphere.collidertransform.rotation.Add(angularvelocity.Multiply(boundingsphere.collidertransform.rotation).Multiply(deltatime / 0.5f));*/
}
void Boundingsphere::handleCollision() {
	float momentiamass = 0;
	vector3 momentums;
	vector3 netforce = collisiondata.forces[0];
	vector3 nettorque;
	float angularimpulse;
	float impulse = 0;
	Raytrace raytrace;
	for (int i = 0; i < collisiondata.otherobjects.size(); i++) {
		momentums = momentums.add(collisiondata.momentia[i].second.multiply(collisiondata.momentia[i].first)); //impulse
		momentiamass += collisiondata.momentia[i].first;

		netforce += collisiondata.forces[i + 1];    //acceleration

		vector3 dir = tempoldpos - collisiondata.otherobjects[i]->tempoldpos;
		if (raytrace.Trace(collisiondata.otherobjects[i]->tempoldpos, dir, tempoldpos, radius)) {  //angle
			impulse = -(1.0f + elasticity);
			impulse *= (collisiondata.otherobjects[i]->tempvel - velocity).dotProduct(raytrace.normal);

			vector3 rb = raytrace.intersectionpoint - tempoldpos;
			vector3 ra = raytrace.intersectionpoint - collisiondata.otherobjects[i]->tempoldpos;
			vector3 angimpa = (ra.crossProduct(raytrace.normal).divide(collisiondata.otherobjects[i]->MOI)).crossProduct(ra);
			vector3 angimpb = (rb.crossProduct(raytrace.normal).divide(MOI)).crossProduct(rb);
			angularimpulse = (angimpa + angimpb).dotProduct(raytrace.normal);

			impulse /= (((1.0f / collisiondata.otherobjects[i]->mass) + (1.0f / mass))/* + angularimpulse*/);

			velocity = velocity - raytrace.normal.multiply((impulse / mass));
			/*netforce += raytrace.normal.multiply((impulse / boundingsphere.mass)).divide(deltatime).negateVector();*/
			angularvelocity = angularvelocity - (rb.crossProduct(raytrace.normal.multiply(angularimpulse))).divide(MOI);
			nettorque += (rb.crossProduct(collisiondata.forces[i + 1]));
		}
		else {
			std::cout << "Something's probably broken." << std::endl;
		}
	}
	/*momentums = momentums.add(boundingsphere.velocity.multiply(boundingsphere.mass));
	/*momentiamass += boundingsphere.mass;
	vector3 newv = momentums.divide(momentiamass);
	/*boundingsphere.acceleration = momentums.divide(deltatime);
	netforce += boundingsphere.acceleration.multiply(boundingsphere.mass + 10.0f);
	boundingsphere.acceleration += netforce.divide(momentiamass * boundingsphere.elasticity + boundingsphere.mass);*/

	/*angularimpulse = nettorque.multiply(deltatime);
	boundingsphere.angularvelocity = angularimpulse.divide(boundingsphere.MOI);*/
	angularacceleration += nettorque.divide(MOI);
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
			neg = collisiondata.otherobjects[i]->collidertransform.position.negateVector();
			neg = neg.Normalize();
			while (intersectionTest(collisiondata.otherobjects[i]->getRadius(), collisiondata.otherobjects[i]->collidertransform.position)) {
				collidertransform.position += neg.multiply(collisiondata.collisiondistance);
				count++;
				if (count > 1) {

				}
				done = false;
			}
			sleep++;
		}
	}
}

void Boundingsphere::setMOI(float _MOI) {
	MOI = _MOI;
}
float Boundingsphere::getMOI()
{
	return MOI;
}
void Boundingsphere::calculateMOI() {
	MOI = (2.0f / 5.0f) * mass * radius * radius;
}
float Boundingsphere::getRadius()
{
	return radius;
}
Boundingsphere::Boundingsphere()
{
	radius = 20.0f;
	collided = false;
	MOI = (2.0f / 5.0f) * mass * radius * radius;
}


Boundingsphere::~Boundingsphere()
{
}
