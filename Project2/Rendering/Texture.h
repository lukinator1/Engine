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
	void loadCubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	void loadIconPixels(std::string filename, unsigned char * &data, int & width, int & height, int & components);
	void bindTexture();
	Texture();
	Texture(std::string filename);
	~Texture();
};

