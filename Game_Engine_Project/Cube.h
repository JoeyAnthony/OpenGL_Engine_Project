#pragma once
#include <glad\glad.h>

#include <vector>
#include "Vec.h"

class Cube
{
public:

	void initCube();
	void drawCube();
	Cube();
	~Cube();
};

class CVertex
{
public:
	float x, y, z;
	float nx, ny, nz;
	float r, g, b, a;
	float tx, ty, tz;

	//Vertex();
	//Vertex(float x, float y, float z, float nx = 0, float ny = 0, float nz = 0, float r = 0, float g = 0, float b = 0, float a = 0, float tx = 0, float ty = 0);
};