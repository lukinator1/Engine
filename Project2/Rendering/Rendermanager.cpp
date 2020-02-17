#include "Rendermanager.h"
Rendering::Rendering()
{
	/*SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); //bit data for 1 pixel
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetSwapInterval(1);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	/*glEnable(GL_FRAMEBUFFER_SRGB);
	glEnable(GL_DEPTH_CLAMP);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
}
void Rendering::renderingStartup(Window &window)
{
	Textrenderer.loadText();
}
void Rendering::renderingShutdown()
{
}
void Rendering::update(Scene &currentscene)
{
	currentscene.renderScene();
}
void Rendering::renderEntity(Entity &gameobject) {
	gameobject.transform.setTranslationVector(vector3(10.0f, 17.5f, 12.0f));
	gameobject.renderEntity(shade);
}
void Rendering::renderScene(Scene &currentscene)
{
	currentscene.root.renderEntity(shade);
	currentscene.skybox.useSkybox();
}
Rendering::~Rendering()
{
}
