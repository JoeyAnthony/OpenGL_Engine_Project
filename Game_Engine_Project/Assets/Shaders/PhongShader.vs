#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 tex;
layout(location = 3) in vec3 normal;

out vec3 vertcolor;
out vec2 texcoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

vec3 lightposition = vec3(2, 2, 2);

void main()
{
	vertcolor = color;
	texcoord = tex;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1.0f);
}