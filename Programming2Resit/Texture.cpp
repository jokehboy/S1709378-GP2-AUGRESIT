#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	int width;
	int height;
	int numOfComponents;

	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numOfComponents, 4);

	

	glGenTextures(1, &textureHandler); //num of address of texs
	glBindTexture(GL_TEXTURE_2D, textureHandler);//bind tex - define type and specify tex we are working w/

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap tex outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap tex outside height
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (tex is smoler than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnification (tex is BEEGER)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);//target, mipmapping, pixel format, width,height,border size, input format, data type of tex and out img data
	stbi_image_free(imageData);

	if (imageData == NULL)
	{
		std::cerr << "Texture load failed you massive idiot" << fileName << std::endl;
	}
}


Texture::~Texture()
{
	glDeleteTextures(1, &textureHandler);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); //check we is workin with one of the 32 texs

	glActiveTexture(GL_TEXTURE0 + unit);//set thy active tex U N I T
	glBindTexture(GL_TEXTURE_2D, textureHandler);//type of and tex to bindus to U N I T

}