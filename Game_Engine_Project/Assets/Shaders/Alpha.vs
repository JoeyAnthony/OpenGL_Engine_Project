#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

out vec3 fnormal;
out vec2 ftexcoord;
out float ftime;

void main()
{
    ftime = time;
    fnormal = normalMatrix * normal;
    ftexcoord = texcoord;

    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1);
}
