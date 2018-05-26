#pragma once
#include <glad\glad.h>
//#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glm\glm.hpp>

class Shader
{
public:
	struct ShaderLocationData
	{
		GLuint modelmatrixloc;
		GLuint viewmatrixloc;
		GLuint projectionmatrixloc;
		GLuint normalmatrixloc;
	};
	ShaderLocationData shaderlocations;

	int shaderid_;

	void UseShader();

	void SetBool(std::string name, bool value);
	void SetInt(std::string name, int value);
	void SetFLoat(std::string name, float value);
	void SetVec3(std::string name, glm::vec3 value);
	void SetVec3Array(std::string name, glm::vec3 v[]);

	void destroy();

	Shader();
	Shader(const Shader* shader);
	Shader(const char * vertex_file_path, const char * fragment_file_path);
	~Shader();
};

