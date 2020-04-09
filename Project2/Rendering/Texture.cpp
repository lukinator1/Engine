#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
int Texture::loadTexture(std::string filename)
{
	filename = "Rendering/Materials/Textures/" + filename;
	int width, height, components;
	int returner = 0;
	unsigned char* data = stbi_load((filename).c_str(), &width, &height, &components, 4);

	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Texture failed to load. May've returned an error texture instead.", 1, 2, true);
		std::cout << filename;
		data = stbi_load("Rendering/Materials/Textures/errortexture.png", &width, &height, &components, 4);
		returner = -1;
	}
	glBindTexture(GL_TEXTURE_2D, textureid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //set options here
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	return returner;
}
void Texture::loadErrorCubeMap(){
	int width, height, components;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid); //todo: check if power of 2
	unsigned char* data = stbi_load("Rendering/Materials/Textures/errortexture.png", &width, &height, &components, 4);
	if (data != NULL) {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
int Texture::loadCubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back)
{
	std::string r = "Rendering/Materials/Textures/Cubemaps/" + right;
	std::string l = "Rendering/Materials/Textures/Cubemaps/" + left;
	std::string t = "Rendering/Materials/Textures/Cubemaps/" + top;
	std::string b = "Rendering/Materials/Textures/Cubemaps/" + bottom;
	std::string f = "Rendering/Materials/Textures/Cubemaps/" + front;
	std::string bck = "Rendering/Materials/Textures/Cubemaps/" + back;
	int width, height, components;
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid);

	unsigned char* data = stbi_load((r).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map didn't load. Returned an error texture instead.", 2, 2, true);
		loadErrorCubeMap();
		return -1;
		/*data = stbi_load("Rendering/Textures/errortexture.png", &width, &height, &components, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);*/
	}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

	data = stbi_load((l).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map didn't load. Returned an error texture instead.", 2, 2, true);
		loadErrorCubeMap();
		return -1;
		/*data = stbi_load("Rendering/Textures/errortexture.png", &width, &height, &components, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);*/
	}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

	data = stbi_load((t).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map didn't load. Returned an error texture instead.", 2, 2, true);
		loadErrorCubeMap();
		return -1;
		/*data = stbi_load("Rendering/Textures/errortexture.png", &width, &height, &components, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);*/
	}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

	data = stbi_load((b).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map didn't load. Returned an error texture instead.", 2, 2, true);
		loadErrorCubeMap();
		return -1;
		/*data = stbi_load("Rendering/Textures/errortexture.png", &width, &height, &components, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);*/
	}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

	data = stbi_load((f).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map didn't load. Returned an error texture instead.", 2, 2, true);
		loadErrorCubeMap();
		return- 1;
		/*data = stbi_load("Rendering/Textures/errortexture.png", &width, &height, &components, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);*/
	}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);

	data = stbi_load((bck).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map didn't load. Returned an error texture instead.", 2, 2, true);
		loadErrorCubeMap();
		return -1;
		/*data = stbi_load("Rendering/Textures/errortexture.png", &width, &height, &components, 4);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);*/
	}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return 0;
}
void Texture::loadIconPixels(std::string filename, unsigned char * &data, int & width, int & height, int & components) {
	data = stbi_load((filename).c_str(), &width, &height, &components, STBI_rgb_alpha);

	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Icon failed to load. Returned default icon instead.", 1, 2, true); //todo
		data = stbi_load("Errorwindowicon.png", &width, &height, &components, STBI_rgb_alpha);
		return;
	}
	else {
		return;
	}
}
void Texture::useTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureid);
}
void Texture::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::useCubeMapTexture() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid);
}
void Texture::freeTexture() {
		glDeleteTextures(1, &textureid);
}
void Texture::loadErrorTexture() {
	loadTexture("errortexture.png");
}
/*void Texture::setTexture(Texture &text) {
	*this = text;
}
void Texture::setTexture(std::string filename) {
	filename = "Rendering/Textures/" + filename;
	int width, height, components;
	unsigned char* data = stbi_load((filename).c_str(), &width, &height, &components, 4);

	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Texture failed to load. Returned an error texture instead.", 1, 2, true);
		data = stbi_load("Rendering/Textures/errortexture.png", &width, &height, &components, 4);
		return;
	}
	glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_2D, textureid);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //set options here
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}*/
Texture::Texture()
{
	glGenTextures(1, &textureid);
}
Texture::Texture(std::string filename)
{
	glGenTextures(1, &textureid);
	loadTexture(filename);
}
Texture::~Texture()
{
}
