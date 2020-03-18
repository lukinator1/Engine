#include "Physicsmanager.h"



void Physicsmanager::Update(Scene & currentscene)
{
	/*for (int i = 0; i < physicsobjects.size(); i++) {
		for (int u = i + 1; i < physicsobjects.size(); i++) {
			physicsobjects[i]->Simulate(*physicsobjects[u]);
		}
	}*/
	for (int i = 0; i < spheres.size(); i++) {
		for (int u = i + 1; i < spheres.size(); i++) {
			spheres[i]->boundingSphereCollision(*spheres[u]);
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
