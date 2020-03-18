#pragma once
#include "Entity.h"
#include "Rendering/Skybox.h"
#include "Rendering/Lighting/Lighting.h"
#include "Physics/Boundingsphere.h"
#include <fstream>
#include <vector>
#include <map>
class Scene
{
public:
	Entity root;
	vector3 ambientlight;
	std::vector<Directionallight *> directionallights; 
	std::vector<Pointlight *> pointlights;
	std::vector<Spotlight *> spotlights;
	std::vector<Boundingsphere > boundedspheres;
	/*std::map<std::string, Directionallight>directionallights;
	std::map<std::string, Pointlight> pointlights;
	std::map<std::string, Spotlight>spotlights;*/
	Skybox skybox;
	void saveScene();
	void initScene();
	void inputScene();
	void setAmbientLight(vector3 alight);
	void renderScene();
	void updateScene();
	Scene();
	void addDirectionalLight(Directionallight &dlight);
	void addSpotLight(Spotlight & slight);
	void addPointLight(Pointlight & plight);
	int setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	/*void setSkybox(Skybox & _skybox);*/
	~Scene();
	void renderScene(Scene & currentscene);
};

