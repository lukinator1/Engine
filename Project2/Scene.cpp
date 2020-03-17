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
	root.entitiesInput();
}
void Scene::setAmbientLight(vector3 alight) {
	ambientlight = alight;
}
void Scene::addDirectionalLight(Directionallight &dlight){
	directionallights.push_back(&dlight);
}
void Scene::addSpotLight(Spotlight &slight) {
	spotlights.push_back(&slight);
}
void Scene::addPointLight(Pointlight &plight) {
	pointlights.push_back(&plight);
}
/*void Scene::removeDirectionalLight(Directionallight &dlight) { //todo: removing
	directionallights.push_back(&dlight);
}
void Scene::addSpotLight(Spotlight &slight) {
	spotlights.push_back(&slight);
}
void Scene::addPointLight(Pointlight &plight) {
	pointlights.push_back(&plight);
}*/
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
