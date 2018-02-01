#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>



namespace Tools
{
	extern int TICKS_PER_SECOND;
	//extern int width;
	//extern int height;

	extern float deltatime;

	/*
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
