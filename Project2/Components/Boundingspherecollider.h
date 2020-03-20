#pragma once
#include "Component.h"
#include "../Physics/Physicsmanager.h"
class Boundingspherecollider : public Component
{
public:
	Boundingsphere boundingsphere;
	 void updateComponent(Transforming &t) {
		 if (boundingsphere.collisiondata.collided == true) {
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
		 t.position = boundingsphere.collidertransform.position;
		 t.rotation = boundingsphere.collidertransform.rotation;
	}
	 void handleCollision(){
		 if (boundingsphere.forces.size() != 0) {

		 }
		 /*boundingsphere.acceleration =*/
		 boundingsphere.velocity.x = -boundingsphere.velocity.x;  //linear movmement
		 boundingsphere.velocity.y = -boundingsphere.velocity.y;
		 boundingsphere.velocity.z = -boundingsphere.velocity.z;

	 }
	 void initializeComponent() {
		 spherecolliders.push_back(&boundingsphere);
	 }
	 Boundingspherecollider(Boundingsphere bsphere)  {
		 boundingsphere = bsphere;
		 /*boundingsphere.position = physicstransform.position;
		 physicstransform = t;*/
	 }
	~Boundingspherecollider();
};

