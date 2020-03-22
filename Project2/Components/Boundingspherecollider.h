#pragma once
#include "Component.h"
#include "../Physics/Physicsmanager.h"
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
			 handleCollision();  //resolve forces/collisions
		 }

		 vector3 acceleration(boundingsphere.acceleration.x, boundingsphere.acceleration.y - boundingsphere.gravity, boundingsphere.acceleration.z);
		 Quaternion angularvelocity(boundingsphere.angularvelocity.x, boundingsphere.angularvelocity.y, boundingsphere.angularvelocity.z, 0);
		 boundingsphere.velocity = boundingsphere.velocity.add(boundingsphere.acceleration.multiply(deltatime));
		 boundingsphere.angularvelocity = boundingsphere.angularvelocity.add(boundingsphere.angularacceleration.multiply(deltatime));

		 boundingsphere.collidertransform.position = boundingsphere.collidertransform.position.add(boundingsphere.velocity.multiply(deltatime)).add(acceleration.multiply((deltatime * deltatime)/0.5f)); //physics calculations here
		 /*boundingsphere.collidertransform.rotation = boundingsphere.collidertransform.rotation.Add(angularvelocity.Multiply(boundingsphere.collidertransform.rotation);
		 torque = boundingsphere.angularvelocity.multiply(boundingsphere.MOI);*/
		 boundingsphere.collidertransform.Rotate(boundingsphere.angularvelocity.multiply(deltatime).add(boundingsphere.angularacceleration.multiply((deltatime * deltatime) / 0.5f)));
		 /*boundingsphere.collidertransform.rotation = boundingsphere.collidertransform.rotation.Add(angularvelocity.Multiply(boundingsphere.collidertransform.rotation).Multiply(deltatime/0.5));*/
		 if (settotransform) {
			 t.position = boundingsphere.collidertransform.position;
			 t.rotation = boundingsphere.collidertransform.rotation;
		 }
	}
	 void handleCollision() {
		 float momentiamass = 0; //linear
		 vector3 momentums;
		 for (int i = 0; i < boundingsphere.momentia.size(); i++) {
			 momentums = momentums.add(boundingsphere.momentia[i].second.multiply(boundingsphere.momentia[i].first));
			 momentiamass += boundingsphere.momentia[i].first;
		 }
		 momentums = momentums.add(boundingsphere.velocity.multiply(boundingsphere.mass));
		 momentiamass += boundingsphere.mass;
		 boundingsphere.velocity = momentums.divide(momentiamass);
		 vector3 netforce = boundingsphere.forces[0];
		 for (int i = 1; i < boundingsphere.forces.size(); i++) {
			 netforce += boundingsphere.forces[i];
		}
		boundingsphere.acceleration = netforce.divide(boundingsphere.mass);

		//angle
		
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

