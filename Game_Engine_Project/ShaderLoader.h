#pragma once
#include <glad\glad.h>
//#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
class ShaderLoader
{
public:
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	ShaderLoader();
	~ShaderLoader();
};

