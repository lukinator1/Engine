#pragma once
#include "../Scene.h"
#include "Boundingsphere.h"
#include "Boundingbox.h"
#include <vector>
class Physicsmanager
{
public:
	std::vector <Physicsobject *> physicsobjects;
	void Update(Scene &currentscene);
	Physicsmanager();
	~Physicsmanager();
};
extern std::vector<Physicsobject *> colliders; //add back to here when scene swaps
