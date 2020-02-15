#include "Scene.h"
Scene::Scene()
{
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
