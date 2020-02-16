#pragma once
#include "Mesh.h"
#include "Materials.h"
#include "Shader.h"
#include "Texture.h"
#include "Transforming.h"
#include "Lighting/Lighting.h"
#include "Vertex.h"
#include "../Scene.h"
#include "../Entity.h"
#include "Skybox.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <vector>
//This is the main component for rendering, with meshes, materials, shaders, lighting and more. 
class Rendering
{
public:
	void renderingStartup();
	void renderingShutdown();
	void update(Scene &currentscene);
	void renderEntity(Entity &gameobject);
	void renderScene(Scene & currentscene);
	Shader shade;
	Rendering();
	~Rendering();
};

