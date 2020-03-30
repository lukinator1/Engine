#pragma once
#include "Component.h"
#include "../Physics/Physicsmanager.h"
class AABBcollider
{
public:
	Boundingbox boundingbox;
	bool settotransform;

	void componentPhysics(Transforming &t) {
		if (settotransform) {
			t.position = boundingbox.getPosition();
			t.rotation = boundingbox.getRotation();
		}
		boundingbox.collisiondata.otherobjects.clear();
		boundingbox.collisiondata.momentia.clear();
		if (boundingbox.collisiondata.forces.size() != 1) {
			boundingbox.collisiondata.forces.erase(boundingbox.collisiondata.forces.begin() + 1, boundingbox.collisiondata.forces.end());
		}
		if (boundingbox.collided != true) {
			boundingbox.tempvel = boundingbox.velocity;
			boundingbox.tempoldpos = boundingbox.oldpos;
		}
		if (boundingbox.collided) {
			boundingbox.collided = false;
		}
	}
	void initializeComponent() {
		colliders.push_back(&boundingbox);
	}
	void setToTransform(bool trans) {
		settotransform = trans;
	}
	AABBcollider(Boundingbox bbox) {
		boundingbox = bbox;
		settotransform = true;
		/*boundingsphere.position = physicstransform.position;
		physicstransform = t;*/
	}
	AABBcollider();
	~AABBcollider();
};

