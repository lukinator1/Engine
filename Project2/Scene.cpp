#include "Scene.h"
Scene::Scene() 
{
}
int Scene::setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back) {
	if (skybox.setSkybox(right, left, top, bottom, front, back) == -1) {
		return -1;
	}
	else {
		return 0;
	}
}
/*void Scene::setSkybox(Skybox &_skybox) {
	skybox.setSkybox(skybox);
}*/
void Scene::saveScene()
{
}
void Scene::initScene()
{
}
void Scene::inputScene()
{
	root.entityInput();
}
void Scene::renderScene()
{
	/*root.renderEntity();*/
}

void Scene::updateScene()
{
	root.updateEntity();
}
Scene::~Scene()
{
}
