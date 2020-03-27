#include "Boundingbox.h"
#include "../Global.h"
bool Boundingbox::Simulate(Physicsobject & otherobject) {
	switch (otherobject.shape) {
	case 0:						//sphere

	break;
	case 1:						//box
		vector3 difference = otherobject.getMinextents().Subtract(maxextents);
		vector3 otherdifference = minextents.Subtract(otherobject.getMaxextents());
		vector3 distance;
		if (difference.x > otherdifference.x) {
			distance.x = difference.x;
		}
		else {
			distance.x = otherdifference.x;
		}
		if (difference.y > otherdifference.y) {
			distance.y = difference.y;
		}
		else {
			distance.y = otherdifference.y;
		}
		if (difference.z > otherdifference.z) {
			distance.z = difference.z;
		}
		else {
			distance.z = otherdifference.z;
		}
		maxdistance = distance.x;
		if (distance.y > maxdistance) {
			maxdistance = distance.y;
		}
		if (distance.z > maxdistance) {
			maxdistance = distance.z;
		}
		if (maxdistance < 0) {
			collided = true;
			/*collisiondata.collisiondistance = collisiondistance;*/
			collisiondata.otherobjects.push_back(&otherobject);
			std::pair <float, vector3> momentum = { otherobject.mass, otherobject.velocity };
			collisiondata.momentia.push_back(momentum);
			collisiondata.forces.push_back(acceleration.multiply(mass));
		}
		else {
			return false;
		}
		break;
	}
	return false;
}
void Boundingbox::Integrate() {
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
	boundingsphere.collidertransform.Rotate(boundingsphere.angularvelocity.multiply(deltatime).add(boundingsphere.angularacceleration.multiply((deltatime * deltatime) / 0.5f)));*/
	collidertransform.rotation = collidertransform.rotation.Add(newangularvelocity.Multiply(collidertransform.rotation).Multiply(deltatime / 0.5f));
}
void Boundingbox::handleCollision() {
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
		if (raytrace.Trace(collisiondata.otherobjects[i]->tempoldpos, dir)) {  //angle
			impulse = -(1.0f + elasticity);
			impulse *= (collisiondata.otherobjects[i]->tempvel - tempvel).dotProduct(raytrace.normal);
			vector3 rb = raytrace.intersectionpoint - tempoldpos;
			vector3 ra = raytrace.intersectionpoint - collisiondata.otherobjects[i]->tempoldpos;
			vector3 angimpa = (ra * raytrace.normal).divide(collisiondata.otherobjects[i]->MOI) * (ra);
			vector3 angimpb = (rb * raytrace.normal).divide(MOI) * rb;
			angularimpulse = (angimpa + angimpb).dotProduct(raytrace.normal);
			impulse /= ((1.0f / collisiondata.otherobjects[i]->mass) + (1.0f / mass) + angularimpulse);

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
void Boundingbox::recalculateMOI() {
	/*MOI = (2.0f / 5.0f) * mass * radius * radius;*/
}
void Boundingbox::setLength(float _length)
{
	length = _length;
	maxextents.z = collidertransform.position.z + (length / 2.0f);
	minextents.z = collidertransform.position.z - (length / 2.0f);
}
void Boundingbox::setWidth(float _width)
{
	width = _width;
	maxextents.x = collidertransform.position.x + (width / 2.0f);
	minextents.x = collidertransform.position.x - (width / 2.0f);
}
void Boundingbox::setHeight(float _height)
{
	height = _height;
	maxextents.y = collidertransform.position.y + (length / 2.0f);
	minextents.y = collidertransform.position.y - (length / 2.0f);
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
Boundingbox::Boundingbox()
{
	shape = 1;
	setLength(20.0f);
	setWidth(20.0f);
	setHeight(20.0f);
	MOI = mass / 12.0f();
}
Boundingbox::~Boundingbox()
{
}
