#pragma once
#include "Engine.h"
#include <string>  //todo: error texture
class Texture : public Logger
{
public:
	GLuint textureid;
	void loadTexture(std::string &filename);
	void bindTexture();
	Texture();
	Texture(std::string filename);
	~Texture();
};

