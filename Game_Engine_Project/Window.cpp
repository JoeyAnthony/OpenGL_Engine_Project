#include "Window.h"



void Window::SetWindowSize(GLuint w, GLuint h)
{
	//initial window size
	width = w;
	height = h;

	if (window != nullptr)
	{
		glfwSetWindowSize(window, w, h);
	}
}

void Window::Resize(GLFWwindow * window, int width, int height)
{

}



void Window::Hints()
{
	//windows hints, set before opening a window
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::Start()
{
	//create window
	window = glfwCreateWindow(width, height, "Game?", NULL, NULL);
	glfwMakeContextCurrent(window);

	//initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Debug("Failed to initialize GLAD" << std::endl);
		//return -1;
	}
}

void Window::StandardSettings()
{
	//scene stuff
	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

GLuint Window::Width()
{
	return width;
}

GLuint Window::Height()
{
	return height;
}

GLFWwindow * Window::GetWindow()
{
	return window;
}

Window::Window()
{
	//initialize GLFW
	int init = glfwInit();
	if (init == GLFW_FALSE)
	{
		printf("Could not Initialize GLFW");
		//return -1;
	}

	//windows hints, set before opening a window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//checking opengl version
	printf("Compiled against GLFW %i.%i.%i\n",
		GLFW_VERSION_MAJOR,
		GLFW_VERSION_MINOR,
		GLFW_VERSION_REVISION);

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Running against GLFW %i.%i.%i\n", major, minor, revision);
}


Window::~Window()
{
	glfwSetWindowShouldClose(window, true);
}
