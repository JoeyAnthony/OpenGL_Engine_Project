#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Texture::LoadTexture(const std::string & fileName)
{
	filepath = fileName;
	unsigned char* imgData;
	stbi_set_flip_vertically_on_load(true);
	imgData = stbi_load(fileName.c_str(), &width, &height, &bpp, 4);


	if (imgData != nullptr)
	{
		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);

		//setting image
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


		glTexImage2D(GL_TEXTURE_2D,
			0,					//level
			GL_RGBA,			//internal format
			width,				//width
			height,				//height
			0,					//border
			GL_RGBA,			//data format
			GL_UNSIGNED_BYTE,	//data type
			imgData);			//data
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(imgData);
		std::cout << "has texture" << std::endl;
	}
	else
	{
		std::cout << "no image" << std::endl;
	}
	Unbind();
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texid);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}



Texture::Texture(const std::string &fileName)
{
	LoadTexture(fileName);
}

Texture::Texture()
{
}


Texture::~Texture()
{
}