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
	forwardambientshader.setAmbientLight(vector3(0.3f, 0.3f, 0.3f));
	dlight.setLight(vector3(0, 0, 1.0f), vector3(1.0f, 1.0f, 1.0f), 0.4f); //make point to lights?
	dlighttwo.setLight(vector3(1.0f, 0, 0), vector3(-1.0f, 1.0f, -1.0f), 0.4f);
	plight.setLight(vector3(0.0f, 0.5f, 1.0f), vector3(2.0f, 0.0f, 7.0f), 4.0f, 2.0f, 0.0f, 1.0f);
	for (int i = 0; i < 10; i++) {
		plight.position.x += 7.0f;
		plight.position.z += 7.0f;
		pointlights.push_back(plight);
	}
	slight.setLight(vector3(0.0f, 1.0f, 1.0f), vector3(5.0f, 0.0f, 5.0f), vector3(1.0f, -1.0f, 1.0f), 80.0f, 0.7f, 3.0f, 0.0f, 0.1f);
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
	temp = dlight;
	dlight = dlighttwo;
	dlighttwo = temp;

	for (int i = 0; i < 1; i++) {
		if (pointlights[i].intensity != 0.0f) {
			forwardpointshader.pointlight = pointlights[i];
			currentscene.root.renderEntity(&forwardpointshader);
		}
	}

	forwardspotshader.spotlight = slight;
	currentscene.root.renderEntity(&forwardspotshader);

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
