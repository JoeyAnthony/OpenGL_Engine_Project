#include "UniformBuffer.h"



void UniformBuffer::updateBuffer()
{
}

void UniformBuffer::updateSubBuffer(int offset, int size, const void* data)
{
	glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
}

void UniformBuffer::bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
}

void UniformBuffer::unbind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBuffer::UniformBuffer(GLuint bytesize, int type, int bindingPoint) : bytesize(bytesize), type(type), bindingPoint(bindingPoint)
{
	glGenBuffers(1, &UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, bytesize, nullptr, type);
	glBindBuffer(GL_UNIFORM_BUFFER, 0); //unbind
	glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, UBO);
}


UniformBuffer::~UniformBuffer()
{
}
