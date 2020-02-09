#include "Shader.h"
Shader::Shader() : directionallight(vector3(0.0f, 0.0f, 0.0f), vector3(0.0f, 0.0f, 0.0f))
{
	ambientlight = vector3(1.0f, 1.0f, 1.0f);
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
	/*for (int i = 0; i < 2; i++) {
		glAttachShader(program, shaders[i]);
	}
	glLinkProgram(program);*/
	/*glGetProgramiv(program, GL_LINK_STATUS, &checkerror);
	/GLint checkerror = 0;
	if (checkerror == GL_FALSE) {
		engineLog(__FILE__, __LINE__, "Warning: Shader failed to link.", 1, 2, true);
		return;
	}*/
	/*glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &checkerror);
	if (checkerror == GL_FALSE) {
		engineLog(__FILE__, __LINE__, "Warning: Shader creation unsuccessful.", 1, 2, true);
		return;
	}*/
}
Shader::~Shader()
{
	glDeleteProgram(program);
	for (int i = 0; i < 2; i++) {
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}
}
std::string Shader::loadShader(const std::string& filename)
{
	std::ifstream fileopener;
	fileopener.open((filename).c_str());

	if (fileopener.is_open()) {
		std::string sourcecode;
		std::string buffer;
		while (getline(fileopener, buffer)) {
			if (fileopener.bad()) {
				engineLog(__FILE__, __LINE__, "Warning: Shader program failed to load. An empty string was returned instead.", 1, 2, true);
				return "";
			}
			sourcecode.append(buffer + "\n");
		}
		return sourcecode;
	}
	else
	{
		engineLog(__FILE__, __LINE__, "Warning: Shader failed to load. An empty string was return instead.", 1, 2, true);
		return "";
	}
}
void Shader::useShader()
{
	glUseProgram(program);
}
void Shader::addVertexShader(const std::string& sourcecode)
{
	createShader(sourcecode, GL_VERTEX_SHADER);
}
void Shader::addFragmentShader(const std::string& sourcecode)
{
	createShader(sourcecode, GL_FRAGMENT_SHADER);
}
void Shader::createShader(const std::string& sourcecode, unsigned int type)
{
	char errorlog[512];
	GLuint shader = glCreateShader(type);
	if (shader == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader didn't create.", 1, 2, true);
	}

	const GLchar* p[1];
	p[0] = sourcecode.c_str();
	GLint lengths[1];
	lengths[0] = sourcecode.length();
	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);
	int checkerror = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &checkerror);
	if (checkerror == GL_FALSE) {
		engineLog(__FILE__, __LINE__, "Warning: Shader failed to compile.", 1, 2, true);
		glGetShaderInfoLog(shader, 512, NULL, errorlog);
		engineLog(__FILE__, __LINE__, errorlog, 1, 2, true);
		return;
	}
	shaders.push_back(shader);
	/*glAttachShader(program, shader);*/
	/*glBindAttribLocation(program, 0, "pos");*/
}
void Shader::compileShader() {
	char errorlog[512];
	for (int i = 0; i < 2; i++) {
		glAttachShader(program, shaders[i]);
	}
	glLinkProgram(program);
	int checkerror;
	glGetProgramiv(program, GL_LINK_STATUS, &checkerror);
	if (checkerror == GL_FALSE) {
		engineLog(__FILE__, __LINE__, "Warning: Shader failed to link.", 1, 2, true);
		glGetShaderInfoLog(program, 512, NULL, errorlog);
		engineLog(__FILE__, __LINE__, errorlog, 1, 2, true);
		return;
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &checkerror);
	if (checkerror == GL_FALSE) {
		engineLog(__FILE__, __LINE__, "Warning: Shader creation unsuccessful.", 1, 2, true);
		return;
	}
}
void Shader::addUniform(std::string newuniform) { //may need to cast this to string
	/*if (newuniform == "directionallight") {
	int uniformlocation = glGetUniformLocation(program, (newuniform + ".color").c_str());
	uniforms.emplace(newuniform + ".color", uniformlocation);
	int uniformlocation = glGetUniformLocation(program, (newuniform + ".color").c_str());
	uniforms.emplace(newuniform, uniformlocation);
	return;
	}*/
	int uniformlocation = glGetUniformLocation(program, newuniform.c_str());
	if (uniformlocation == -1) {
		engineLog(__FILE__, __LINE__, "Uniform: " + newuniform + " failed to add.", 1, 2, true);
	}
	uniforms.emplace(newuniform, uniformlocation);
}
void Shader::setUniform(std::string newuniform, int newintvalue) {
	glUniform1i(uniforms.at(newuniform.c_str()), newintvalue);
}
void Shader::setUniform(std::string newuniform, float newfloatvalue) {
	glUniform1f(uniforms.at(newuniform.c_str()), newfloatvalue);
}
void Shader::setUniform(std::string newuniform, vector3 newvec3value) {
	glUniform3f(uniforms.at(newuniform.c_str()), newvec3value.x, newvec3value.y, newvec3value.z);
}
void Shader::setUniform(std::string newuniform, matrix4f newmatrixvalue) {
	glUniformMatrix4fv(uniforms.at(newuniform.c_str()), 1, true, &(newmatrixvalue.m[0][0]));
}
/*void Shader::setUniform(std::string newuniform, Light alight) {
	setUniform(newuniform + ".base", alight.color);
	setUniform(newuniform + ".direction", alight.direction);
} directional*/
void Shader::setUniform(std::string newuniform, Directionallight alight) {
	setUniform(newuniform + ".color", alight.getColor());
	setUniform(newuniform + ".direction", alight.getDirection());
	setUniform(newuniform + ".intensity", alight.getIntensity());
}
void Shader::updateUniforms(matrix4f worldmatrix, matrix4f projectedmatrix, Materials &material) { //make case for colors? (and in vertex shader)
	setUniform("transform", projectedmatrix);
	setUniform("color", material.getColor());
	setUniform("ambientlight", ambientlight);
	setUniform("directionallight", directionallight);
	material.texture.bindTexture();
}
void Shader::setAmbientLight(vector3 newambientlight) {
	newambientlight = newambientlight.Normalize();
	ambientlight = newambientlight;
}
void Shader::setDirectionalLight(Directionallight newdlight) {
	directionallight = newdlight;
}
vector3 Shader::getAmbientLight() {
	return ambientlight;
}
Directionallight Shader::getDirectionalLight() {
	return directionallight;
}
