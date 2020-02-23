#pragma once
#include "../Logger.h"
#include <string>  //todo: = overload, .setTexture()
#include <fstream>
#include <GL/glew.h>
class Texture : public Logger
{
private:
	GLuint textureid;
public:
	void loadTexture(std::string filename);
	void loadErrorCubeMap();
	void loadCubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	void loadIconPixels(std::string filename, unsigned char * &data, int & width, int & height, int & components);
	void useTexture();
	void useCubeMapTexture();
	/*void setTexture(Texture &text);
	void setTexture(std::string newtext);*/
	Texture();
	Texture(std::string filename);
	~Texture();
};

