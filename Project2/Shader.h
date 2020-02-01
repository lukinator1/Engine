#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Engine.h"
class Shader : public Logger
{
private:
	unsigned int program;
	enum shadertype {
	};
public:
	std::string loadShader(const std::string& filename);
	void useShader();
	void addVertexShader(const std::string& program);
	void addFragmentShader(const std::string& program);
	std::vector<GLuint> shaders;
	void createShader(const std::string& sourcecode, unsigned int type);
	void compileShader();

	Shader();
	~Shader();
};

