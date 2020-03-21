#include "Physicsmanager.h"



void Physicsmanager::Update(Scene & currentscene)
{
	/*for (int i = 0; i < physicsobjects.size(); i++) {
		for (int u = i + 1; i < physicsobjects.size(); i++) {
			physicsobjects[i]->Simulate(*physicsobjects[u]);
		}
	}*/
	for (int i = 0; i < spherecolliders.size(); i++) {
		for (int u = 0; u < spherecolliders.size(); u++) {
			if (i != u) {
				spherecolliders[i]->boundingSphereCollision(*spherecolliders[u]);
			}
		}
	}
	currentscene.root.updateEntities();
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
