#pragma once
#include "Component.h"
#include "../Physics/Boundingsphere.h"
class Boundingspherecollider : public Component
{
public:
	Boundingsphere boundingsphere;
	 void updateComponent(Transforming &t) {
		 if (boundingsphere.collided == true) {
			 std::cout << "collided" << std::endl;
		 }
		 boundingsphere.collidertransform.position = boundingsphere.collidertransform.position.add(boundingsphere.velocity.multiply(deltatime));
		 t = boundingsphere.collidertransform;
	}
	 Boundingspherecollider(Boundingsphere bsphere)  {
		 boundingsphere = bsphere;
		 /*boundingsphere.position = physicstransform.position;
		 physicstransform = t;*/
	 }
	~Boundingspherecollider();
};

