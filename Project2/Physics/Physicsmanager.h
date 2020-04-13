#pragma once
#include "../Scene.h"
#include "Boundingsphere.h"
#include "Boundingbox.h"
#include <vector>
class Physicsmanager
{
public:
	bool noclip = false;
	void Impulse(); //todo
	void Update(Scene &currentscene);
	Physicsmanager();
	~Physicsmanager();
};
extern std::vector<Physicsobject *> colliders; //add back to here when scene swaps
