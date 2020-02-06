#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
void Texture::loadTexture(std::string filename)
{
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
