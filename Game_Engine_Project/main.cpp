//GLAD
#include <glad\glad.h>
//#define GLFW_DLL
#include <GLFW\glfw3.h>

#include <vector>
#include <iostream>

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

#include "Window.h"
#include "Input.h"
#include "Tools.h"
#include "GameSetup.h"

int UPDATE_TICKS_PER_SECOND = 60;
int SKIP_UPDATE_TICKS = 1000 / UPDATE_TICKS_PER_SECOND;

int FIXED_TICKS_PER_SECOND = 25;
int SKIP_FIXED_TICKS = 1000 / FIXED_TICKS_PER_SECOND;
int MAX_FRAMESKIP = 5;

double next_update_game_tick;
double next_fixed_game_tick;

int loops;

float interpolation;
float fixedinterpolation;

void ErrorCallbak(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
	//std::cout << description << std::endl;
}


void Display(GLFWwindow* window)
{
	glClearColor(0.35f, 0.64f, 0.99f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		
	glfwSwapBuffers(window);
	Tools::UpdateDeltaTime(glfwGetTime());
}

void FrameBufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void MainWindowClose(GLFWwindow* window)
{
	glfwSetWindowShouldClose(window, true);
}

#include "GameObject.h"
#include "CameraComponent.h"
int main(int argc, char* argv[])
{
	glfwSetErrorCallback(ErrorCallbak);
	Window window;
	window.SetWindowSize(1280, 720);
	window.Hints();
	window.Start();
	window.StandardSettings();

	next_update_game_tick = glfwGetTime();
	next_fixed_game_tick = glfwGetTime();
	

	glfwSetWindowCloseCallback(window.GetWindow(), MainWindowClose);
	glfwSetKeyCallback(window.GetWindow(), Keyboard::KeyCallback);
	glfwSetFramebufferSizeCallback(window.GetWindow(), FrameBufferSize);
	glfwSetMouseButtonCallback(window.GetWindow(), Mouse::MouseButtonCallback);
	glfwSetCursorPosCallback(window.GetWindow(), Mouse::MouseCursorPosCallback);
	glfwSetCursorEnterCallback(window.GetWindow(), Mouse::MouseEnterCallback);

	//glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glViewport(0, 0, window.Width(), window.Height());


	GameSetup setup(&window);
	setup.CreateScene();


	while (!glfwWindowShouldClose(window.GetWindow()))
	{
		Tools::ToolsLoop();

		loops = 0;
		//fixed gameloop, FIXED_TICKS_PER_SECOND times a second
		while (Tools::Time() > next_fixed_game_tick && loops < MAX_FRAMESKIP)
		{
			Tools::ToolsFixedUpdate();

			setup.FixedUpdateScene();

			next_fixed_game_tick += SKIP_FIXED_TICKS;
			loops++;
		}

		//update loop, UPDATE_TICKS_PER_SECOND times a second
		while (Tools::Time() > next_update_game_tick)
		{
			Tools::ToolsUpdate();

			setup.UpdateScene();
			setup.LateUpdateScene();

		
			//translate
			//float pos = glfwGetTime() * 5;
			//position = glm::vec3(glm::cos(pos), glm::sin(pos), 0);
			//position /= 2;

			//rotate
			//rotation.y += 45.0f  * Tools::DeltaTime();

			//scale
			//float scaling = glm::sin(glfwGetTime() * 3) / 2.0f + 1.5f;
			//scale = scaling * glm::vec3(1, 1, 1);

			next_update_game_tick += SKIP_UPDATE_TICKS;
		}
		interpolation = (Tools::Time() + SKIP_UPDATE_TICKS - next_update_game_tick) / (float)SKIP_UPDATE_TICKS;
		fixedinterpolation = (Tools::Time() + SKIP_FIXED_TICKS - next_fixed_game_tick) / (float)SKIP_FIXED_TICKS;

		////render scene
		////Display(window);

		//glClearColor(0.6f, 0.14f, 1.0f, 0.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		setup.Render();

		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();	

		////print ticks in console
		//std::cout << "DeltaTIme: " << Tools::DeltaTime() << std::endl;
		//std::cout << "interpolation: " << interpolation << std::endl;
		//std::cout << "fixedinterpolation: " << fixedinterpolation << std::endl;
		//std::cout << "wpos: " << cam.position.x <<" "<< cam.position.y << " " << cam.position.z << std::endl;
	}

	glfwTerminate();
	return 0;
}

//using friend classes to make a specific class use specific function in another
//like a main class setting keyboard vars
//need to put this code in a class and use main file for making this class