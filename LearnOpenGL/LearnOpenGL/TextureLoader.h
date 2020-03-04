#pragma once

#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H


#include "stb_image.h"

#include <glad/glad.h>
#include <iostream>
#include <vector>

class TextureLoader {
public:
	static void loadTexture(unsigned int& texture, std::string path);
	static void loadTexture(unsigned int& texture, const char* path);
	static void loadCubeTexture(unsigned int& texture, std::string path);
	static void setWrap(unsigned int wrap);
	static void setMinFilter(unsigned int filter);
	static void setMaxFilter(unsigned int filter);
private:
	static unsigned int textureWrap;
	static unsigned int minFilter;
	static unsigned int maxFilter;
};

#endif