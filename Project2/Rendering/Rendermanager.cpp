#include "Rendermanager.h"
Rendering::Rendering() : forwardambientshader("Forwardambient"), forwarddirectionalshader("Forwarddirectional"), forwardpointshader("Forwardpoint"), forwardspotshader("Forwardspot") {

}
void Rendering::renderingStartup(Window &window)
{
	/*SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //bit data for 1 pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);*/
	windowptr = &window;
	Textrenderer.loadText();
}
void Rendering::update(Scene &currentscene)
{
	currentscene.renderScene();
}
void Rendering::renderEntity(Entity &gameobject, Shader * &shade) {
	gameobject.renderEntity(shade);
}
void Rendering::renderEntities(Entity &gameobject, Shader * &shade) {
	gameobject.renderEntities(shade);
}
void Rendering::renderScene(Scene &currentscene){
	forwardambientshader.ambientlight = currentscene.ambientlight;  //todo: optimize with pointers
	currentscene.root->renderEntities(&forwardambientshader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(false);
	glDepthFunc(GL_EQUAL);

	for (int i = 0; i < currentscene.directionallights.size(); i++) {
		forwarddirectionalshader.setDirectionalLight(*currentscene.directionallights[i]);
		currentscene.root->renderEntities(&forwarddirectionalshader);
	}

	for (int i = 0; i < 1; i++) {
		forwardpointshader.pointlight = (*currentscene.pointlights[i]);
		currentscene.root->renderEntities(&forwardpointshader);
	}


	/*for (int i = 0; i < currentscene.spotlights.size(); i++) {
		forwardspotshader.spotlight = (*currentscene.spotlights[i]);
		currentscene.root->renderEntities(&forwardspotshader);
	}*/

	glDepthFunc(GL_LESS);
	glDepthMask(true);
	glDisable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ZERO);

	if (currentscene.skybox.skyboxbox.size != 0) {
	currentscene.skybox.useSkybox();
	}
}
vector3 Rendering::getAmbientLight() {
	return forwardambientshader.ambientlight;
}
void Rendering::setAmbientLight(vector3 _ambientlight)
{
	forwardambientshader.ambientlight = _ambientlight;
}
void Rendering::setAmbientLight(float x, float y, float z)
{
	forwardambientshader.ambientlight.x = x;
	forwardambientshader.ambientlight.y = y;
	forwardambientshader.ambientlight.z = z;
}
void Rendering::renderingShutdown()
{
	windowptr->closeWindow();
}
Rendering::~Rendering()
{
}
