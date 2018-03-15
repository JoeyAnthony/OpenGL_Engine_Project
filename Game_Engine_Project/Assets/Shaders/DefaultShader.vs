#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 tex;
layout(location = 3) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec3 vertColor;

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0f);
    vertColor = color;
}

