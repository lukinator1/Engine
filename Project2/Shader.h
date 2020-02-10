#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "Engine.h"
#include "Materials.h"
#include "Directionallight.h"
#include "Pointlight.h"
#include "Camera.h"
class Shader : public Logger
{
private:
	unsigned int program;
	std::map<std::string, int> uniforms;
	enum shadertype {
	};
public:
	vector3 ambientlight;
	Directionallight directionallight;
	Pointlight* pointlights[5];
	std::string loadShader(const std::string& filename);
	void useShader();
	void addVertexShader(const std::string& program);
	void addFragmentShader(const std::string& program);
	std::vector<GLuint> shaders;
	void createShader(const std::string& sourcecode, unsigned int type);
	void compileShader();
	void addUniform(std::string newuniform);
	void setUniform(std::string newuniform, int value);
	void setUniform(std::string newuniform, float newfloatvalue);
	void setUniform(std::string newuniform, vector3 newvec3value);
	void setUniform(std::string newuniform, matrix4f newmatrixvalue);
	void setUniform(std::string newuniform, Directionallight alight);
	void setUniform(std::string newuniform, Pointlight alight);
	void updateUniforms(matrix4f worldmatrix, matrix4f projectedmatrix, vector3 position, Materials &material);
	vector3 getAmbientLight();
	Directionallight getDirectionalLight();
	Pointlight** getPointLights();
	/*void setDirectionalLight(Directionallight newdlight);*/
	void setAmbientLight(vector3 newambientlight);

	Shader();
	~Shader();
};

