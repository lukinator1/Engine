#pragma once
#include "Component.h"
#include "../Physics/Physicsmanager.h"
#include "../Physics/Raytrace.h"
class Boundingspherecollider : public Component
{
public:
	Boundingsphere boundingsphere;
	bool settotransform;
	void componentPhysics(Transforming &t) {
		if (settotransform) {
			t.position = boundingsphere.collidertransform.position;
			t.rotation = boundingsphere.collidertransform.rotation;
		}
		boundingsphere.collisiondata.otherobjects.clear();
		boundingsphere.collisiondata.momentia.clear();
		if (boundingsphere.collisiondata.forces.size() != 1) {
			boundingsphere.collisiondata.forces.erase(boundingsphere.collisiondata.forces.begin() + 1, boundingsphere.collisiondata.forces.end());
		}
		if (boundingsphere.collided != true) {
			boundingsphere.tempvel = boundingsphere.velocity;
			boundingsphere.tempoldpos = boundingsphere.oldpos;
		}
		if (boundingsphere.collided) {
			boundingsphere.collided = false;
		}
	}
	/*void Integrate(Transforming &t) {
		if (boundingsphere.collided == true) {
			boundingsphere.tempoldpos = boundingsphere.oldpos;
			boundingsphere.tempvel = boundingsphere.velocity;
			handleCollision();  //resolve forces/collisions
		}
		boundingsphere.oldpos = boundingsphere.collidertransform.position;
		vector3 acceleration(boundingsphere.acceleration.x, boundingsphere.acceleration.y - boundingsphere.gravity, boundingsphere.acceleration.z);
		Quaternion angularvelocity(boundingsphere.angularvelocity.x, boundingsphere.angularvelocity.y, boundingsphere.angularvelocity.z, 0);
		boundingsphere.velocity = boundingsphere.velocity.add(boundingsphere.acceleration.multiply(deltatime));
		boundingsphere.angularvelocity = boundingsphere.angularvelocity.add(boundingsphere.angularacceleration.multiply(deltatime));

		boundingsphere.collidertransform.position = boundingsphere.collidertransform.position.add(boundingsphere.velocity.multiply(deltatime)).add(acceleration.multiply((deltatime * deltatime) / 0.5f)); //physics calculations here
		/*boundingsphere.collidertransform.rotation = boundingsphere.collidertransform.rotation.Add(angularvelocity.Multiply(boundingsphere.collidertransform.rotation);
		torque = boundingsphere.angularvelocity.multiply(boundingsphere.MOI);
		/*boundingsphere.collidertransform.Rotate(boundingsphere.angularvelocity.multiply(deltatime).add(boundingsphere.angularacceleration.multiply((deltatime * deltatime) / 0.5f)));
		boundingsphere.collidertransform.rotation = boundingsphere.collidertransform.rotation.Add(angularvelocity.Multiply(boundingsphere.collidertransform.rotation).Multiply(deltatime / 0.5f));
	}
	/*void handleCollision() {
		float momentiamass = 0;
		vector3 momentums;
		vector3 netforce = boundingsphere.collisiondata.forces[0];
		vector3 nettorque;
		float angularimpulse;
		float impulse = 0;
		Raytrace raytrace;
		for (int i = 0; i < boundingsphere.collisiondata.otherobjects.size(); i++) {
			momentums = momentums.add(boundingsphere.collisiondata.momentia[i].second.multiply(boundingsphere.collisiondata.momentia[i].first)); //impulse
			momentiamass += boundingsphere.collisiondata.momentia[i].first;

			netforce += boundingsphere.collisiondata.forces[i + 1];    //acceleration

			vector3 dir = boundingsphere.tempoldpos - boundingsphere.collisiondata.otherobjects[i]->tempoldpos;
			if (raytrace.Trace(boundingsphere.collisiondata.otherobjects[i]->tempoldpos, dir, boundingsphere.tempoldpos, boundingsphere.radius)) {  //angle
				impulse = -(1.0f + boundingsphere.elasticity);
				impulse *= (boundingsphere.collisiondata.otherobjects[i]->tempvel - boundingsphere.velocity).dotProduct(raytrace.normal);

				vector3 rb = raytrace.intersectionpoint - boundingsphere.tempoldpos;
				vector3 ra = raytrace.intersectionpoint - boundingsphere.collisiondata.otherobjects[i]->tempoldpos;
				vector3 angimpa = (ra.crossProduct(raytrace.normal).divide(boundingsphere.collisiondata.otherobjects[i]->MOI)).crossProduct(ra);
				vector3 angimpb = (rb.crossProduct(raytrace.normal).divide(boundingsphere.MOI)).crossProduct(rb);
				angularimpulse = (angimpa + angimpb).dotProduct(raytrace.normal);
 
				impulse /= (((1.0f / boundingsphere.collisiondata.otherobjects[i]->mass) + (1.0f / boundingsphere.mass))/* + angularimpulse);

				boundingsphere.velocity = boundingsphere.velocity - raytrace.normal.multiply((impulse / boundingsphere.mass));
				/*netforce += raytrace.normal.multiply((impulse / boundingsphere.mass)).divide(deltatime).negateVector();
				boundingsphere.angularvelocity = boundingsphere.angularvelocity - (rb.crossProduct(raytrace.normal.multiply(angularimpulse))).divide(boundingsphere.MOI);
				nettorque += (rb.crossProduct(boundingsphere.collisiondata.forces[i + 1]));
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
		boundingsphere.angularvelocity = angularimpulse.divide(boundingsphere.MOI);
		boundingsphere.angularacceleration += nettorque.divide(boundingsphere.MOI);
	}*/
	void initializeComponent() {
		colliders.push_back(&boundingsphere);
	}
	void setToTransform(bool trans) {
		settotransform = trans;
	}
	Boundingspherecollider(Boundingsphere bsphere) {
		boundingsphere = bsphere;
		settotransform = true;
		/*boundingsphere.position = physicstransform.position;
		physicstransform = t;*/
	}
	~Boundingspherecollider();
};
