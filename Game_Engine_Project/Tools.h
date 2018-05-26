#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

#ifdef _DEBUG
//#define Debug(x) std::cout << x
	#define Debug(x) 
#else
#define Debug(x) 
#endif 

namespace Tools
{
	extern int TICKS_PER_SECOND;
	//extern int width;
	//extern int height;

	extern float deltatime;

	static bool debug = false;

	/**
	update deltatime values
	*/
	void UpdateDeltaTime(double time);

	///*
	//update update time values
	//*/
	//void SetLastUpdatePerSecond(double time);

	///*
	//update fixed update time values
	//*/
	//void SetLastFixedUpdatesPerSecond(double time);
	
	/*
	get deltatime
	*/
	const float DeltaTime();

	const float Time(bool seconds = false);

	float lerp(float v0, float v1, float t);
	glm::vec3 lerp(glm::vec3 vec0, glm::vec3 vec1, float t);
	
	float angleLerp(float a0, float a1, float t);

	glm::vec3 screenToWorld(glm::vec2 mousepos, glm::mat4 view, glm::mat4 projection, int screenwidth, int screenheight);

	///*
	//get number of updates per second
	//*/
	//float UpdatesPerSecond();

	///*
	//get number of fixedupdates per second
	//*/
	float FixedUpdatesPerSecond();

	void ToolsUpdate();
	void ToolsFixedUpdate();
	void ToolsLoop();
}
