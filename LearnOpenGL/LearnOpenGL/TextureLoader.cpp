#define STB_IMAGE_IMPLEMENTATION
#include "TextureLoader.h"

unsigned int TextureLoader::textureWrap = GL_REPEAT;
unsigned int TextureLoader::minFilter = GL_LINEAR_MIPMAP_LINEAR;
unsigned int TextureLoader::maxFilter = GL_LINEAR;

void TextureLoader::init()
{
	stbi_set_flip_vertically_on_load(true);
}

void TextureLoader::loadTexture(unsigned int & texture, std::string path)
{
	loadTexture(texture, path.c_str());
}

void TextureLoader::loadTexture(unsigned int & texture, const char * path)
{
	int width, height, nrChannels;
	glGenTextures(1, &texture);
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1)format = GL_RED;
		if (nrChannels == 3)format = GL_RGB;
		if (nrChannels == 4)format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFilter);
		
	}
	else {
		std::cout << "Failed to load texture: " << path << std::endl;
	}
	stbi_image_free(data);
}

void TextureLoader::setWrap(unsigned int wrap)
{
	textureWrap = wrap;
}

void TextureLoader::setMinFilter(unsigned int filter)
{
	minFilter = filter;
}

void TextureLoader::setMaxFilter(unsigned int filter)
{
	maxFilter = filter;
}
