#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 tex;

out vec3 vertcolor;
out vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vertcolor = color;
	texcoord = tex;
	gl_Position = projection * view * model * vec4(pos, 1.0f);
}