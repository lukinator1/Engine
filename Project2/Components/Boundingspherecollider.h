#pragma once
#include "Component.h"
#include "../Physics/Physicsmanager.h"
#include "../Physics/Raytrace.h"
class Boundingspherecollider : public Component
{
public:
	Boundingsphere boundingsphere;
	bool settotransform;
	 void updateComponent(Transforming &t) {
		 if (boundingsphere.collided == true) {
			/* for (int i = 0; i < boundingsphere.collisiondata.size(); i++) {
				 boundingsphere
			 }*/
			 boundingsphere.tempvel = boundingsphere.velocity;
			 handleCollision();  //resolve forces/collisions
		 }

		 boundingsphere.oldpos = boundingsphere.collidertransform.position;
		 vector3 acceleration(boundingsphere.acceleration.x, boundingsphere.acceleration.y - boundingsphere.gravity, boundingsphere.acceleration.z);
		 Quaternion angularvelocity(boundingsphere.angularvelocity.x, boundingsphere.angularvelocity.y, boundingsphere.angularvelocity.z, 0);
		 boundingsphere.velocity = boundingsphere.velocity.add(boundingsphere.acceleration.multiply(deltatime));
		 boundingsphere.angularvelocity = boundingsphere.angularvelocity.add(boundingsphere.angularacceleration.multiply(deltatime));

		 boundingsphere.collidertransform.position = boundingsphere.collidertransform.position.add(boundingsphere.velocity.multiply(deltatime)).add(acceleration.multiply((deltatime * deltatime)/0.5f)); //physics calculations here
		 /*boundingsphere.collidertransform.rotation = boundingsphere.collidertransform.rotation.Add(angularvelocity.Multiply(boundingsphere.collidertransform.rotation);
		 torque = boundingsphere.angularvelocity.multiply(boundingsphere.MOI);*/
		 /*boundingsphere.collidertransform.Rotate(boundingsphere.angularvelocity.multiply(deltatime).add(boundingsphere.angularacceleration.multiply((deltatime * deltatime) / 0.5f)));*/
		 boundingsphere.collidertransform.rotation = boundingsphere.collidertransform.rotation.Add(angularvelocity.Multiply(boundingsphere.collidertransform.rotation).Multiply(deltatime/0.5));
		 if (settotransform) {
			 t.position = boundingsphere.collidertransform.position;
			 t.rotation = boundingsphere.collidertransform.rotation;
		 }

		 if (boundingsphere.collided != true){
			 boundingsphere.tempvel = boundingsphere.velocity;
		 }
		 if (boundingsphere.collided) {
			 boundingsphere.collided = false;
		 }
	}
	 void handleCollision() {
		 float momentiamass = 0;
		 vector3 momentums;
		 vector3 netforce = boundingsphere.collisiondata.forces[0];
		 vector3 nettorque;
		 vector3 angularimpulse;
		 float impulse = 0;
		 Raytrace raytrace;
		 for (int i = 0; i < boundingsphere.collisiondata.otherobjects.size(); i++) {
			 momentums = momentums.add(boundingsphere.collisiondata.momentia[i].second.multiply(boundingsphere.collisiondata.momentia[i].first)); //impulse
			 momentiamass += boundingsphere.collisiondata.momentia[i].first;

			 netforce += boundingsphere.collisiondata.forces[i + 1];    //acceleration

			 vector3 dir = boundingsphere.oldpos - boundingsphere.collisiondata.otherobjects[i]->oldpos;
			 /*std::vector <Physicsobject *> ignore = { &boundingsphere};
			 raytrace.Trace(boundingsphere.collisiondata.otherobjects[i]->oldpos, dir);
			 vector3 dir = boundingsphere.oldpos - raytrace.intersectionpoint;*/
			 if (raytrace.Trace(boundingsphere.collisiondata.otherobjects[i]->oldpos, dir, &boundingsphere)) {  //angle
				 nettorque += (raytrace.intersectionpoint - boundingsphere.collidertransform.position).crossProduct(boundingsphere.collisiondata.forces[i + 1]);
				 impulse = -(1.0f + boundingsphere.elasticity);
				 impulse *= (boundingsphere.collisiondata.otherobjects[i]->tempvel - boundingsphere.velocity).dotProduct(raytrace.normal);
				 impulse /= ( (1.0f/boundingsphere.collisiondata.otherobjects[i]->mass) + (1.0f / boundingsphere.mass));
				 boundingsphere.velocity = boundingsphere.velocity - raytrace.normal.multiply((impulse / boundingsphere.mass));
			 }
			 else {
				 std::cout << "Something's probably broken." << std::endl;
			 }
		}
		momentums = momentums.add(boundingsphere.velocity.multiply(boundingsphere.mass));
		momentiamass += boundingsphere.mass;
		vector3 newv = momentums.divide(momentiamass);
		/*boundingsphere.acceleration = momentums.divide(deltatime);
		boundingsphere.acceleration = netforce.divide(boundingsphere.mass);*/

		angularimpulse = nettorque.multiply(deltatime);
		boundingsphere.angularvelocity = angularimpulse.divide(boundingsphere.MOI);
		boundingsphere.angularacceleration = nettorque.divide(boundingsphere.MOI);
		

		boundingsphere.collisiondata.otherobjects.clear();
		boundingsphere.collisiondata.momentia.clear();
		if (boundingsphere.collisiondata.forces.size() != 1) {
			boundingsphere.collisiondata.forces.erase(boundingsphere.collisiondata.forces.begin() + 1, boundingsphere.collisiondata.forces.end());
		}
		 /*boundingsphere.acceleration += boundingsphere.resultingdirection/boundingsphere.mass;
		 boundingsphere.acceleration =*/
		 /*boundingsphere.velocity.x = -boundingsphere.velocity.x;  //linear movmement
		 boundingsphere.velocity.y = -boundingsphere.velocity.y;
		 boundingsphere.velocity.z = -boundingsphere.velocity.z;*/

	 }
	 void initializeComponent() {
		 spherecolliders.push_back(&boundingsphere);
	 }
	 void setToTransform(bool trans) {
		 settotransform = trans;
	 }
	 Boundingspherecollider(Boundingsphere bsphere)  {
		 boundingsphere = bsphere;
		 settotransform = true;
		 /*boundingsphere.position = physicstransform.position;
		 physicstransform = t;*/
	 }
	~Boundingspherecollider();
};

