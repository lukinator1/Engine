#pragma once
#include "Entity.h"
#include <fstream>
class Scene
{
public:
	Entity root;
	void saveScene();
	Scene();
	~Scene();
};

