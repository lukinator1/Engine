#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "GL/glew.h"
#include "Materials.h"
#include "Lighting/Lighting.h"
#include "../Mathlibrary/Mathlibrary.h"
class Shader : public Logger
{
private:
	unsigned int program;
	int type; //0 = ambient, 1 = directional, 2 = point, 3 = spot, 4 = text, 5 = skybox
	std::map<std::string, int> uniforms;
public:
	vector3 ambientlight;
	Directionallight directionallight;
	Pointlight* pointlights[5];
	Pointlight pointlight;
	Spotlight spotlight;
	Spotlight* spotlights[5];
	std::string loadShader(std::string filename);
	void setShader(std::string shadertype);
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
	void setUniform(std::string newuniform, Spotlight alight);
	void updateUniforms(const matrix4f &worldmatrix, const matrix4f &projectedmatrix, const vector3 &position, Materials &material);
	vector3 getAmbientLight();
	Directionallight getDirectionalLight();
	Pointlight** getPointLights();
	Spotlight ** getSpotLights();
	void setDirectionalLight(Directionallight newdlight);
	/*void setPointLight(Pointlight* newplight);*/
	void setAmbientLight(vector3 newambientlight);

	Shader();
	Shader(std::string filename);
	~Shader();
};

