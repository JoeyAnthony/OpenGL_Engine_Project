#include "Tools.h"
#include <glm\gtc\constants.hpp>

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



float Tools::lerp(float v0, float v1, float t)
{
	return (1.0f - t) * v0 + t * v1;
}

glm::vec3 Tools::lerp(glm::vec3 vec0, glm::vec3 vec1, float t)
{
	return (1.0f - t) * vec0 + t * vec1;
}



//float Tools::shortAngleDist(float a0, float a1)
//{
//	float max = glm::two_pi<float>();
//	float da = std::fmod((a1 - a0), max);
//	return 2* std::fmod(da, (max - da));
//}
//
//
//float Tools::angleLerp(float a0, float a1, float t)
//{
//	return a0 + shortAngleDist(a0, a1)*t;
//}



glm::vec3 Tools::screenToWorld(glm::vec2 mousepos, glm::mat4 view, glm::mat4 projection, int screenwidth, int screenheight)
{
	
	float x = (2.0f * mousepos.x) / (float)screenwidth - 1.0f;
	float y = 1.0f - (2.0f * mousepos.y) / (float)screenwidth;
	float z = 0.0f;

	glm::mat4 inv = glm::inverse(projection * view);
	glm::vec4 pos = inv * glm::vec4(x, y, z, 1.0f);
	pos = pos / pos.w;

	return pos;
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
