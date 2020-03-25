#include "Physicsmanager.h"



void Physicsmanager::Update(Scene & currentscene)
{
	/*for (int i = 0; i < physicsobjects.size(); i++) {
		for (int u = i + 1; i < physicsobjects.size(); i++) {
			physicsobjects[i]->Simulate(*physicsobjects[u]);
		}
	}*/
	for (int i = 0; i < spherecolliders.size(); i++) {  //test collisions
		for (int u = 0; u < spherecolliders.size(); u++) {
			if (i != u) {
				spherecolliders[i]->Simulate(*spherecolliders[u]);
			}
		}
	}
	for (int i = 0; i < spherecolliders.size(); i++) {  //handle collisions, update new velocities/positions
		spherecolliders[i]->Integrate();
	}
	/*for (int i = 0; i < spherecolliders.size(); i++) {
		spherecolliders[i]->handleConstraints();
	}*/
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
