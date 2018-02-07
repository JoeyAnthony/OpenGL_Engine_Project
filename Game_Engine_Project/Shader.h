#pragma once
#include <glad\glad.h>
//#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Shader
{
public:
	struct ShaderLocationData
	{
		GLuint modelmatrixloc;
		GLuint viewmatrixloc;
		GLuint projectionmatrixloc;
	};
	ShaderLocationData shaderlocations;

	int shaderid_;

	void UseShader();

	void SetBool(std::string name, bool value);
	void SetInt(std::string name, int value);
	void SetFLoat(std::string name, float value);

	Shader();
	Shader(const char * vertex_file_path, const char * fragment_file_path);
	~Shader();
};

