#pragma once
#include "Entity.h"
#include "Rendering/Skybox.h"
#include <fstream>
class Scene
{
public:
	Entity root;
	Skybox skybox;
	void saveScene();
	void initScene();
	void inputScene();
	void renderScene();
	void updateScene();
	Scene();
	void setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	void setSkybox(Skybox & _skybox);
	~Scene();
	void renderScene(Scene & currentscene);
};

