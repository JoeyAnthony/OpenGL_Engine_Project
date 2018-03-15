#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 texcoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
//uniform vec3 camPos;
vec3 camPos = vec3(0, 0, 0);

out vec3 fnormal;
out vec3 fcampos;
out vec3 fpos;

void main()
{
    fnormal = normalMatrix * normal;
    fcampos = camPos;
    fpos = pos;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1);
}
