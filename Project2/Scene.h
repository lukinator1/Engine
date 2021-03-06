#pragma once
#include "Entity.h"
#include "Rendering/Skybox.h"
#include "Rendering/Lighting/Lighting.h"
#include "Audio/Audioclip.h"
#include <fstream>
#include <vector>
#include <map>
class Scene
{
private:
public:
	Entity *root;
	vector3 ambientlight;
	std::vector<Directionallight *> directionallights; 
	std::vector<Pointlight *> pointlights;
	std::vector<Spotlight *> spotlights;
	Audioclip *currentsong;
	Skybox skybox;
	Entity *getRoot();
	void setRoot(Entity *e);
	Entity * findEntity(std::string id);
	void saveScene();
	void initScene();
	void closeScene();
	void inputScene();
	void setCurrentSong(Audioclip &song);
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

