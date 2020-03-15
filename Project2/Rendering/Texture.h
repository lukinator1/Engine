#pragma once
#include "../Logger.h"
#include <string>  //todo: = overload, .setTexture()
#include <fstream>
#include <GL/glew.h>
class Texture : public Logger
{
private:
public:
	GLuint textureid;
	void loadTexture(std::string filename);
	void loadErrorCubeMap();
	int loadCubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);
	void loadIconPixels(std::string filename, unsigned char * &data, int & width, int & height, int & components);
	void useTexture();
	void useCubeMapTexture();
	void freeTexture();
	/*void setTexture(Texture &text);
	void setTexture(std::string newtext);*/
	Texture();
	Texture(std::string filename);
	~Texture();
};

