#include "Physicsmanager.h"



void Physicsmanager::Update(Scene & currentscene)
{
	/*for (int i = 0; i < physicsobjects.size(); i++) {
		for (int u = i + 1; i < physicsobjects.size(); i++) {
			physicsobjects[i]->Simulate(*physicsobjects[u]);
		}
	}*/
	for (int i = 0; i < colliders.size(); i++) {  //test collisions
		for (int u = 0; u < colliders.size(); u++) {
			if (i != u) {
				colliders[i]->Simulate(*colliders[u]);
			}
		}
	}
	for (int i = 0; i < colliders.size(); i++) {
		if (colliders[i]->collided) {
			colliders[i]->handleConstraints();
		}
	}
	for (int i = 0; i < colliders.size(); i++) {  //handle collisions, update new velocities/positions
		colliders[i]->Integrate();
	}
	currentscene.root.updatePhysics();

	/*for (int i = 0; i < boxes.size(); i++) {
		for (int u = i + 1; i < boxes.size(); i++) {
			boxes[i]->boundingSphereCollision(*boxes[u]);
		}
	}*/
}

Physicsmanager::Physicsmanager()
{
}


Physicsmanager::~Physicsmanager()
{
}
