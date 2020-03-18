#pragma once
#include "../Scene.h"
#include "Boundingsphere.h"
#include "Boundingbox.h"
#include "Planecollider.h"
#include <vector>
class Physicsmanager
{
public:
	std::vector <Physicsobject *> physicsobjects;
	std::vector <Boundingsphere *> spheres;
	void Update(Scene &currentscene);
	void Collision();
	Physicsmanager();
	~Physicsmanager();
};

