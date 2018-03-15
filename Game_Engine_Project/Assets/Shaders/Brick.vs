#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

out vec3 fnormal;
out vec2 ftexcoord;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    fnormal = normalMatrix * normal;
    ftexcoord = texcoord;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1);
    //gl_Position = modelViewProjectionMatrix * vec4(pos,1);
}
