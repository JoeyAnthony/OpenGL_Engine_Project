#pragma once
#include "glad/glad.h"

class UniformBuffer
{
private:
	GLuint UBO;
	GLuint bytesize;
	int type;
	int bindingPoint;

public:

	void updateBuffer();
	void updateSubBuffer(int offset, int size, const void* data);
	void bind();
	void unbind();

	UniformBuffer(GLuint bytesize, int type, int bindingPoint);
	UniformBuffer() {};
	~UniformBuffer();
};

