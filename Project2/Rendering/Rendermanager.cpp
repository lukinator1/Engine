#include "Rendermanager.h"
Rendering::Rendering() : forwardambientshader("Forwardambient"), forwarddirectionalshader("Forwarddirectional"), forwardpointshader("Forwardpoint")
{
}
void Rendering::renderingStartup(Window &window)
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //bit data for 1 pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	windowptr = &window;
	Textrenderer.loadText();
	dlight.setLight(vector3(0, 0, 1.0f), vector3(1.0f, 1.0f, 1.0f), .4f);
	dlighttwo.setLight(vector3(1.0f, 0, 0), vector3(-1.0f, 1.0f, -1.0f), .4f);
	plight.setLight(vector3(0, 1.0f, 0), vector3(5.0f, 0, 5.0f), 300.0f, 0.8f);
	forwardpointshader.pointlights[0] = &plight;
}
void Rendering::update(Scene &currentscene)
{
	currentscene.renderScene();
}
void Rendering::renderEntity(Entity &gameobject, Shader *shade) {
	gameobject.renderEntity(shade);
}
void Rendering::renderScene(Scene &currentscene)
{
	currentscene.root.renderEntity(&forwardambientshader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(false);
	glDepthFunc(GL_EQUAL);
	forwarddirectionalshader.setDirectionalLight(dlight);
	currentscene.root.renderEntity(&forwarddirectionalshader);
	Directionallight temp = dlight;
	dlight = dlighttwo;
	dlighttwo = temp;
	forwarddirectionalshader.setDirectionalLight(dlight);
	currentscene.root.renderEntity(&forwarddirectionalshader);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_ONE, GL_ZERO);
	glDepthMask(true);
	glDisable(GL_BLEND);
	temp = dlight;
	dlight = dlighttwo;
	dlighttwo = temp;

	currentscene.root.renderEntity(&forwardpointshader);

	if (currentscene.skybox.skyboxbox.size != 0) {
	currentscene.skybox.useSkybox();
	}
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
