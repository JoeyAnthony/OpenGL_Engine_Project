#pragma once
#include <glad\glad.h>

#include <iostream>
#include <string>


class Texture
{
public:
	GLuint texid = 0;
	GLuint texSampler = 0;
	GLuint texSamplerID = 0;
	std::string type;
	std::string filepath;

	int width, height, bpp;
	void LoadTexture(const std::string &fileName);
	void Bind();
	void Unbind();

	Texture();
	Texture(const Texture &tex);
	Texture(const std::string path);

	~Texture();
};

