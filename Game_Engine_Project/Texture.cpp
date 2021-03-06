#include "Texture.h"
#include "Tools.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void Texture::LoadTexture(const std::string & path)
{
	filepath = path;
	unsigned char* imgData;
	stbi_set_flip_vertically_on_load(true);
	imgData = stbi_load(path.c_str(), &width, &height, &bpp, 4);


	if (imgData != nullptr)
	{
		glGenTextures(1, &texid);
		glBindTexture(GL_TEXTURE_2D, texid);

		//setting image
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

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
		Debug("has texture" << std::endl);
	}
	else
	{
		Debug("no image" << std::endl);
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

void Texture::freeData()
{
	//glDeleteTextures(1, &texid);
}



Texture::Texture(const Texture &tex)
{
	this->texid = tex.texid;
	this->texSampler = tex.texSampler;
	this->texSamplerID = tex.texSamplerID;
	this->type = tex.type;
	this->filepath = tex.filepath;
	this->width = tex.width;
	this->height = tex.height;
	this->bpp = tex.bpp;
}

Texture::Texture(const std::string path)
{
	LoadTexture(path);
}

Texture::Texture()
{
}


Texture::~Texture()
{
	
}