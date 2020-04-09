#include "Scene.h"
#include "Physics/Physicsmanager.h"
Scene::Scene() 
{
	ambientlight.setVector(0.75f, 0.75, 0.75f);
}
int Scene::setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back) {
	if (skybox.setSkybox(right, left, top, bottom, front, back) == -1) {
		return -1;
	}
	else {
		return 0;
	}
}
Entity Scene::getRoot()
{
	return root;
}
void Scene::setRoot(Entity &e)
{
	root = e;
}
/*void Scene::setSkybox(Skybox &_skybox) {
	skybox.setSkybox(skybox);
}*/
void Scene::saveScene()
{
}
void Scene::initScene()
{
	root.initializeEntities();
	currentsong->playAudio();
}
void Scene::closeScene() {
	colliders.clear();
	currentsong->endAudio();
}
void Scene::inputScene()
{
	root.entitiesInput();
}
void Scene::setCurrentSong(Audioclip & song)
{
	currentsong = &song;
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
	/*root.renderEntity(); 7*/
}

void Scene::updateScene()
{
	root.updateEntity();
}
Scene::~Scene()
{
}
