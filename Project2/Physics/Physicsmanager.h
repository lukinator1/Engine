#pragma once
#include "../Scene.h"
#include "Boundingsphere.h"
#include "Boundingbox.h"
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
extern std::vector<Boundingsphere *> spherecolliders; //add back to here when scene swaps
