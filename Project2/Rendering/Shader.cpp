#include "Shader.h"
Shader::Shader() : directionallight(vector3(1.0f, 1.0f, 1.0f), vector3(1.0f, 1.0f, 1.0f))
{
	/*type = "phong";
	ambientlight = vector3(1.0f, 1.0f, 1.0f);
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
	addVertexShader(loadShader("Phongvertexshader.vs"));
	addFragmentShader(loadShader("Phongfragmentshader.fs"));
	compileShader();
	addUniform("cameraposition");
	addUniform("color");
	addUniform("transform");
	addUniform("projectedtransform");
	addUniform("ambientlight");
	addUniform("specularintensity");
	addUniform("specularexponent");
	addUniform("directionallight");
	addUniform("pointlights");
	addUniform("spotlights");*/
}
Shader::Shader(std::string shadertype) : directionallight(vector3(1.0f, 1.0f, 1.0f), vector3(1.0f, 1.0f, 1.0f))
{
	/*if (shadertype == "Phong" || shadertype == "phong") {
		type = "phong";
		ambientlight = vector3(1.0f, 1.0f, 1.0f);
		program = glCreateProgram();
		if (program == 0) {
			engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
		}
		addVertexShader(loadShader("Phongvertexshader.vs"));
		addFragmentShader(loadShader("Phongfragmentshader.fs"));
		compileShader();
		addUniform("cameraposition");
		addUniform("color");
		addUniform("transform");
		addUniform("projectedtransform");
		addUniform("ambientlight");
		addUniform("specularintensity");
		addUniform("specularexponent");
		addUniform("directionallight");
		addUniform("pointlights");
		addUniform("spotlights");
	}*/
	if (shadertype == "Colliderdebug" || shadertype == "colliderdebug") {
		type = 6;
		program = glCreateProgram();
		if (program == 0) {
			engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
		}
		addVertexShader(loadShader("Colliderdebugshader.vs"));
		addFragmentShader(loadShader("Colliderdebugshader.fs"));
		compileShader();
		addUniform("transform");
		addUniform("color");
		addUniform("textured");
	}
	else if (shadertype == "Skybox" || shadertype == "skybox") {
	type = 5;
	ambientlight = vector3(1.0f, 1.0f, 1.0f);
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
		addVertexShader(loadShader("Skyboxvertexshader.vs"));
		addFragmentShader(loadShader("Skyboxfragmentshader.fs"));
		compileShader();
		addUniform("skyboxmatrix");
	}
	else if (shadertype == "Textshader" || shadertype == "textshader"){
		type = 4;
		ambientlight = vector3(1.0f, 1.0f, 1.0f);
		program = glCreateProgram();
		if (program == 0) {
			engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
		}
		addVertexShader(loadShader("Textvertexshader.vs"));
		addFragmentShader(loadShader("Textfragmentshader.fs"));
		compileShader();
		addUniform("textmatrix");
		addUniform("textcolor");
	}
	else if (shadertype == "Forwardambient" || shadertype == "forwardambient") {
		type = 0;
		ambientlight = vector3(0.30f, 0.30f, 0.30f);
		program = glCreateProgram();
		if (program == 0) {
			engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
		}
		addVertexShader(loadShader("Ambientforwardvertexshader.vs"));
		addFragmentShader(loadShader("Ambientforwardfragmentshader.fs"));
		compileShader();
		addUniform("color");
		addUniform("transform");
		addUniform("ambientintensity");
		addUniform("textured");
	}
	else if (shadertype == "Forwarddirectional" || shadertype == "forwarddirectional") {
		type = 1;
		directionallight.setIntensity(0.1f);
		program = glCreateProgram();
		if (program == 0) {
			engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
		}
		addVertexShader(loadShader("Directionalforwardvertexshader.vs"));
		addFragmentShader(loadShader("Directionalforwardfragmentshader.fs"));
		compileShader();
		addUniform("cameraposition");
		addUniform("color");
		addUniform("transform");
		addUniform("projectedtransform");
		addUniform("specularintensity");
		addUniform("specularexponent");
		addUniform("directionallight");
	}
	else if (shadertype == "Forwardpoint" || shadertype == "forwardpoint") {
		type = 2;
		program = glCreateProgram();
		if (program == 0) {
			engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
		}
		addVertexShader(loadShader("Pointforwardvertexshader.vs"));
		addFragmentShader(loadShader("Pointforwardfragmentshader.fs"));
		compileShader();
		addUniform("cameraposition");
		addUniform("color");
		addUniform("transform");
		addUniform("projectedtransform");
		addUniform("specularintensity");
		addUniform("pointlight");
		addUniform("specularexponent");
	}
	else if (shadertype == "Forwardspot" || shadertype == "forwardspot") {
		type = 3;
		program = glCreateProgram();
		if (program == 0) {
			engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
		}
		addVertexShader(loadShader("Spotforwardvertexshader.vs"));
		addFragmentShader(loadShader("Spotforwardfragmentshader.fs"));
		compileShader();
		addUniform("cameraposition");
		addUniform("color");
		addUniform("transform");
		addUniform("projectedtransform");
		addUniform("specularintensity");
		addUniform("specularexponent");
		addUniform("spotlight");
	}
	else {
		engineLog(__FILE__, __LINE__, "Warning: Shader failed to create, a valid filename wasn't passed in.", 1, 2, true);
	}
}
Shader::~Shader()
{
	glDeleteProgram(program);
	for (int i = 0; i < shaders.size(); i++) {
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}
}
void Shader::setShader(std::string shadertype) {
/*if (shadertype == "Phong" || shadertype == "phong") {
	type = "phong";
	ambientlight = vector3(1.0f, 1.0f, 1.0f);
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
	addVertexShader(loadShader("Phongvertexshader.vs"));
	addFragmentShader(loadShader("Phongfragmentshader.fs"));
	compileShader();
	addUniform("cameraposition");
	addUniform("color");
	addUniform("transform");
	addUniform("projectedtransform");
	addUniform("ambientlight");
	addUniform("specularintensity");
	addUniform("specularexponent");
	addUniform("directionallight");
	addUniform("pointlights");
	addUniform("spotlights");
}*/
if (shadertype == "Skybox" || shadertype == "skybox") {
	type = 5;
	ambientlight = vector3(1.0f, 1.0f, 1.0f);
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
	addVertexShader(loadShader("Skyboxvertexshader.vs"));
	addFragmentShader(loadShader("Skyboxfragmentshader.fs"));
	compileShader();
	addUniform("skyboxmatrix");
}
else if (shadertype == "Textshader" || shadertype == "textshader") {
	type = 4;
	ambientlight = vector3(1.0f, 1.0f, 1.0f);
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
	addVertexShader(loadShader("Textvertexshader.vs"));
	addFragmentShader(loadShader("Textfragmentshader.fs"));
	compileShader();
	addUniform("textmatrix");
	addUniform("textcolor");
}
else if (shadertype == "Forwardambient" || shadertype == "forwardambient") {
	type = 0;
	ambientlight = vector3(0.2f, 0.2f, 0.2f);
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
	addVertexShader(loadShader("Ambientforwardvertexshader.vs"));
	addFragmentShader(loadShader("Ambientforwardfragmentshader.fs"));
	compileShader();
	addUniform("transform");
	addUniform("color");
	addUniform("ambientintensity");
	addUniform("textured");
}
else if (shadertype == "Forwarddirectional" || shadertype == "forwarddirectional") {
	type = 1;
	directionallight.setIntensity(0.1f);
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
	addVertexShader(loadShader("Directionalforwardvertexshader.vs"));
	addFragmentShader(loadShader("Directionalforwardfragmentshader.fs"));
	compileShader();
	addUniform("cameraposition");
	addUniform("color");
	addUniform("transform");
	addUniform("projectedtransform");
	addUniform("specularintensity");
	addUniform("specularexponent");
	addUniform("directionallight");
}
else if (shadertype == "Forwardpoint" || shadertype == "forwardpoint") {
	type = 2;
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
	addVertexShader(loadShader("Pointforwardvertexshader.vs"));
	addFragmentShader(loadShader("Pointforwardfragmentshader.fs"));
	compileShader();
	addUniform("cameraposition");
	addUniform("color");
	addUniform("transform");
	addUniform("projectedtransform");
	addUniform("specularintensity");
	addUniform("pointlight");
	addUniform("specularexponent");
}
else if (shadertype == "Forwardspot" || shadertype == "forwardspot") {
	type = 3;
	program = glCreateProgram();
	if (program == 0) {
		engineLog(__FILE__, __LINE__, "Warning: Shader program failed to create.", 1, 2, true);
	}
	addVertexShader(loadShader("Spotforwardvertexshader.vs"));
	addFragmentShader(loadShader("Spotforwardfragmentshader.fs"));
	compileShader();
	addUniform("cameraposition");
	addUniform("color");
	addUniform("transform");
	addUniform("projectedtransform");
	addUniform("specularintensity");
	addUniform("specularexponent");
	addUniform("spotlight");
}
else {
	engineLog(__FILE__, __LINE__, "Warning: Shader failed to create, a valid filename wasn't passed in.", 1, 2, true);
	}
}
std::string Shader::loadShader(std::string filename)
{
	std::ifstream fileopener;
	filename = "Rendering/Shaders/" + filename;
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
	if (newuniform == "directionallight") {
		addUniform("directionallight.color");
		addUniform("directionallight.intensity");
		addUniform("directionallight.direction");
	return;
	}
	else if (newuniform == "pointlights") {
		for (int i = 0; i < 5; i++) {
			addUniform("pointlights[" + std::to_string(i) + "].color");
			addUniform("pointlights[" + std::to_string(i) + "].intensity");
			addUniform("pointlights[" + std::to_string(i) + "].attenuation.linearterm");
			addUniform("pointlights[" + std::to_string(i) + "].attenuation.quadraticterm");
			addUniform("pointlights[" + std::to_string(i) + "].position");
			addUniform("pointlights[" + std::to_string(i) + "].range");
		}
	return;
	}
	else if (newuniform == "pointlight") {
		addUniform("pointlight.color");
		addUniform("pointlight.intensity");
		addUniform("pointlight.attenuation.linearterm");
		addUniform("pointlight.attenuation.quadraticterm");
		addUniform("pointlight.position");
		addUniform("pointlight.range");
		return;
	}
	else if (newuniform == "spotlights") {
		for (int i = 0; i < 5; i++) {
			addUniform("spotlights[" + std::to_string(i) + "].color");
			addUniform("spotlights[" + std::to_string(i) + "].intensity");
			addUniform("spotlights[" + std::to_string(i) + "].attenuation.linearterm");
			addUniform("spotlights[" + std::to_string(i) + "].attenuation.quadraticterm");
			addUniform("spotlights[" + std::to_string(i) + "].position");
			addUniform("spotlights[" + std::to_string(i) + "].range");
			addUniform("spotlights[" + std::to_string(i) + "].direction");
			addUniform("spotlights[" + std::to_string(i) + "].cutoff");
			}
	return;
	}
	else if (newuniform == "spotlight") {
		for (int i = 0; i < 5; i++) {
			addUniform("spotlight.color");
			addUniform("spotlight.intensity");
			addUniform("spotlight.attenuation.linearterm");
			addUniform("spotlight.attenuation.quadraticterm");
			addUniform("spotlight.position");
			addUniform("spotlight.range");
			addUniform("spotlight.direction");
			addUniform("spotlight.cutoff");
		}
		return;
	}
	int uniformlocation = glGetUniformLocation(program, newuniform.c_str());
	if (uniformlocation == -1) {
		engineLog(__FILE__, __LINE__, "Uniform: " + newuniform + " failed to add.", 1, 2, true);
	}
	uniforms.emplace(newuniform, uniformlocation);
}
void Shader::setUniform(std::string newuniform, int newintvalue) { //error handling for bad inputs here
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
void Shader::setUniform(std::string newuniform, Directionallight alight) { //directionallight
	setUniform(newuniform + ".color", alight.color);
	setUniform(newuniform + ".direction", alight.direction);
	setUniform(newuniform + ".intensity", alight.intensity);
}
void Shader::setUniform(std::string newuniform, Pointlight alight) {  //pointlight
	setUniform(newuniform + ".color", alight.color);
	setUniform(newuniform + ".intensity", alight.intensity);
	setUniform(newuniform + ".attenuation.linearterm", alight.linearterm);
	setUniform(newuniform + ".attenuation.quadraticterm", alight.quadraticterm);
	setUniform(newuniform + ".position", alight.position);
	setUniform(newuniform + ".range", alight.range);
}
void Shader::setUniform(std::string newuniform, Spotlight alight) {  //spotlight
	setUniform(newuniform + ".color", alight.color);
	setUniform(newuniform + ".intensity", alight.intensity);
	setUniform(newuniform + ".attenuation.linearterm", alight.linearterm);
	setUniform(newuniform + ".attenuation.quadraticterm", alight.quadraticterm);
	setUniform(newuniform + ".position", alight.position);
	setUniform(newuniform + ".range", alight.range);
	setUniform(newuniform + ".direction", alight.direction);
	setUniform(newuniform + ".cutoff", alight.cutoff);
}
void Shader::updateUniforms(const matrix4f &worldmatrix, const matrix4f &projectedmatrix, const vector3 &position, Materials &material) { 
	/*(type == "phong") {
		setUniform("transform", worldmatrix);
		setUniform("projectedtransform", projectedmatrix);
		setUniform("color", material.getColor());
		setUniform("ambientlight", ambientlight);
		setUniform("directionallight", directionallight);
		for (int i = 0; i < 5; i++) {
			if (pointlights[i] != nullptr) {
				setUniform("pointlights[" + std::to_string(i) + ']', *pointlights[i]);
			}
			if (spotlights[i] != nullptr) {
				setUniform("spotlights[" + std::to_string(i) + ']', *spotlights[i]);
			}
		}
		setUniform("specularintensity", material.specularintensity);
		setUniform("specularexponent", material.specularexponent);
		setUniform("cameraposition", position);
		material.texture.useTexture();
	}*/
	if (type == 0) {
		setUniform("transform", projectedmatrix);
		setUniform("ambientintensity", ambientlight);
		setUniform("color", material.getColor());
		if (material.texture.textureactive) {
			setUniform("textured", 1);
			material.texture.useTexture();
		}
		else
		 {
			setUniform("textured", 0);
			material.texture.unbindTexture();
		}
	}
	else if (type == 1) {
		setUniform("transform", worldmatrix);
		setUniform("projectedtransform", projectedmatrix);
		setUniform("color", material.getColor());
		setUniform("directionallight", directionallight);
		setUniform("specularintensity", material.specularintensity);
		setUniform("specularexponent", material.specularexponent);
		setUniform("cameraposition", position);
		if (material.texture.textureactive) {
			material.texture.useTexture();
		}
		else {
			material.texture.unbindTexture();
		}
	}
	else if (type == 2) {
		setUniform("transform", worldmatrix);
		setUniform("projectedtransform", projectedmatrix);
		setUniform("color", material.getColor());
		setUniform("pointlight", pointlight);
		setUniform("specularintensity", material.specularintensity);
		setUniform("specularexponent", material.specularexponent);
		setUniform("cameraposition", position);
		if (material.texture.textureactive) {
			material.texture.useTexture();
		}
		else {
			material.texture.unbindTexture();
		}
	}
	else if (type == 3) {
		setUniform("transform", worldmatrix);
		setUniform("projectedtransform", projectedmatrix);
		setUniform("color", material.getColor());
		setUniform("spotlight", spotlight);
		setUniform("specularintensity", material.specularintensity);
		setUniform("specularexponent", material.specularexponent);
		setUniform("cameraposition", position);
		if (material.texture.textureactive) {
			material.texture.useTexture();
		}
		else {
			material.texture.unbindTexture();
		}
	}
	else if (type == 6) {
		setUniform("transform", projectedmatrix);
		setUniform("color", material.getColor());
		if (material.texture.textureactive) {
			setUniform("textured", 1);
			material.texture.useTexture();
		}
		else {
			setUniform("textured", 0);
			material.texture.unbindTexture();
		}
	}
}
void Shader::setAmbientLight(vector3 newambientlight) { //todo
	ambientlight = newambientlight;
}
void Shader::setDirectionalLight(Directionallight newdlight) {
	directionallight.setLight(newdlight);
}
/*void Shader::setPointLight(Pointlight* newplight) {
	pointlights = newplight;
}*/
vector3 Shader::getAmbientLight() {
	return ambientlight;
}
Directionallight Shader::getDirectionalLight() {
	return directionallight;
}
Pointlight** Shader::getPointLights() {
	return pointlights;
}
Spotlight** Shader::getSpotLights() {
	return spotlights;
}

