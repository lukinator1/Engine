#pragma once
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transforming.h"
#include "Materials.h"
#include <string>
#include <fstream>
//todo: infintely scaling, sizing
class Skybox : public Logger
{
public:
	unsigned int program;
	Texture skyboxtexture;
	Shader skyboxshader;
	Mesh skyboxbox;
	Transforming t;
	void useSkybox();
	Skybox();
	Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	void setSkybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	void setSkybox(Skybox &_skybox);
	~Skybox();
};

