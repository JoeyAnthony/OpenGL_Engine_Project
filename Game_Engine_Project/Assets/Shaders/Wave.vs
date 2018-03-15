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

    float y = pos.y + sin( mod( floor(pos.x), 2 ) + ftime) * 2;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix *
                                                vec4(pos.x, y, pos.z, 1);
}
