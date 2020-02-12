#pragma once
#include "../Logger.h"
#include <string>  //todo: error texture, = overload, .setTexture()
#include <fstream>
#include <GL/glew.h>
class Texture : public Logger
{
public:
	GLuint textureid;
	void loadTexture(std::string filename);
	void bindTexture();
	Texture();
	Texture(std::string filename);
	~Texture();
};

