#include "Scene.h"
Scene::Scene() 
{
}
void Scene::setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back) {
	skybox.setSkybox(right, left, top, bottom, front, back);
}
void Scene::setSkybox(Skybox &_skybox) {
	skybox.setSkybox(skybox);
}
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
