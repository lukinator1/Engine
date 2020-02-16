#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
void Texture::loadTexture(std::string filename)
{
	filename = "Rendering/Textures/" + filename;
	int width, height, components;
	unsigned char* data = stbi_load((filename).c_str(), &width, &height, &components, 4);

	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Texture failed to load. Returned an error texture instead.", 1, 2, true);
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
}
void Texture::loadCubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back)
{
	std::string r = "Rendering/Textures/Cubemaps/" + right;
	std::string l = "Rendering/Textures/Cubemaps/" + left;
	std::string t = "Rendering/Textures/Cubemaps/" + top;
	std::string b = "Rendering/Textures/Cubemaps/" + bottom;
	std::string f = "Rendering/Textures/Cubemaps/" + front;
	std::string bck = "Rendering/Textures/Cubemaps/" + back;
	int width, height, components;
	glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureid);

	unsigned char* data = stbi_load((r).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map face " + right + " didn't load. Returned an error texture instead.", 1, 2, true);
		return; //error instead
	}
	else {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	data = stbi_load((l).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map face " + left + " didn't load. Returned an error texture instead.", 1, 2, true);
		return; //error instead
	}
	else {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	data = stbi_load((t).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map face " + top + " didn't load. Returned an error texture instead.", 1, 2, true);
		return; //error instead
	}
	else {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	data = stbi_load((b).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map face " + bottom + " didn't load. Returned an error texture instead.", 1, 2, true);
		return; //error instead
	}
	else {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	data = stbi_load((f).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map face " + front + " didn't load. Returned an error texture instead.", 1, 2, true);
		return; //error instead
	}
	else {
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	data = stbi_load((bck).c_str(), &width, &height, &components, 4);
	if (data == NULL) {
		engineLog(__FILE__, __LINE__, "Warning: Cube map face " + back + " didn't load. Returned an error texture instead.", 1, 2, true);
		return; //error instead
	}
	else {
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
void Texture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureid);
}
Texture::Texture()
{
}
Texture::Texture(std::string filename)
{
	loadTexture(filename);
}
Texture::~Texture()
{
	glDeleteTextures(1, &textureid);
}
