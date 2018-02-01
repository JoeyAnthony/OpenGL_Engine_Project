#include "Tools.h"

namespace Tools
{
	//int width, height;
	float deltatime;

	double new_time;
	double old_time;

	double old_updateticks;
	double new_updateticks;

	double old_fixedupdateticks;
	double new_fixedupdateticks;
}




void Tools::UpdateDeltaTime(double time)
{
	old_time = new_time;
	new_time = time;

	deltatime = new_time - old_time;
}

//void Tools::SetLastUpdatePerSecond(double time)
//{
//	old_updateticks = new_updateticks;
//	new_updateticks = time;
//}
//
//void Tools::SetLastFixedUpdatesPerSecond(double time)
//{
//	old_fixedupdateticks = new_fixedupdateticks;
//	new_fixedupdateticks = time;
//}

const float Tools::DeltaTime()
{
	return deltatime;
	
}

const float Tools::Time(bool seconds)
{
	if (seconds)
		return glfwGetTime();
	return glfwGetTime() * 1000;
}

void Tools::ToolsUpdate()
{
	UpdateDeltaTime(glfwGetTime());
}

void Tools::ToolsFixedUpdate()
{
}

void Tools::ToolsLoop()
{
	
}

//float Tools::UpdatesPerSecond()
//{
//	return 1000.0f/(new_updateticks - old_updateticks);
//}
//
//float Tools::FixedUpdatesPerSecond()
//{
//	return 1000.0f / (new_fixedupdateticks - old_fixedupdateticks);
//}
