#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <iostream>

#include "Tools.h"

class Window
{
private:
	GLFWwindow* window;
	GLuint width, height;


public:
	void SetWindowSize(GLuint w, GLuint h);
	void Resize(GLFWwindow * window, int width, int height);
	void Hints();
	void Start();
	void StandardSettings();
	

	GLuint Width();
	GLuint Height();

	GLFWwindow* GetWindow();


	Window();
	~Window();
};

