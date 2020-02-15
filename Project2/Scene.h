#pragma once
#include "Entity.h"
#include <fstream>
class Scene
{
public:
	Entity root;
	void saveScene();
	void initScene();
	void inputScene();
	void renderScene();
	void updateScene();
	Scene();
	~Scene();
	void renderScene(Scene & currentscene);
};

