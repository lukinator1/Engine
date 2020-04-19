#include "Physicsmanager.h"



void Physicsmanager::Update(Scene & currentscene)
{
	if (noclip == false) {
		for (int i = 0; i < colliders.size(); i++) {  //test collisions
			for (int u = 0; u < colliders.size(); u++) {
				if (i != u) {
					colliders[i]->Simulate(*colliders[u]);
				}
			}
		}
		for (int i = 0; i < colliders.size(); i++) { //handle constraints
			if (colliders[i]->collided) {
				colliders[i]->handleConstraints();
			}
		}
	for (int i = 0; i < colliders.size(); i++) {  //handle collisions, update new velocities/positions
		colliders[i]->Integrate();
	}
	}
	currentscene.root->updatePhysics();
}

Physicsmanager::Physicsmanager()
{
}


Physicsmanager::~Physicsmanager()
{
}
