#pragma once
#include "Mesh.h"
#include "Materials.h"
#include "Shader.h"
#include "Texture.h"
#include "Transforming.h"
#include "Rendertext.h"
#include "Lighting/Lighting.h"
#include "Vertex.h"
#include "../Scene.h"
#include "../Entity.h"
#include "Skybox.h"
#include "../Window.h"
#include "../Logger.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>
//This is the main component for rendering, with meshes, materials, shaders, lighting and more. 
class Rendering : public Logger
{
public:
	Window* windowptr;
	void renderingStartup(Window &window);
	void renderingShutdown();
	void update(Scene &currentscene);
	void renderEntity(Entity &gameobject, Shader *shade);
	void renderScene(Scene & currentscene);
	void setAmbientLight(vector3 _ambientlight);
	void setAmbientLight(float x, float y, float z);
	void setDirectionalLight(vector3 _ambientlight);
	void setDirectionalLight(float x, float y, float z);
	vector3 ambientlight;
	Directionallight dlight;
	Directionallight dlighttwo;
	Shader phongshader;
	Shader forwardambientshader;
	Shader forwarddirectionalshader;
	Shader otherdirectional;
	Rendertext Textrenderer;
	Rendering();
	~Rendering();
};

