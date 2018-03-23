#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in vec3 tangent;

//matices
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

//camera position
uniform vec3 camPos;
//uniform vec3 lightPos;
vec3 lightPos = vec3(0, 0, 0); //will be uniform later

//out vars
//out vec3 fnormal;

out VS_OUT
{
   vec2 texCoord;
   vec3 tangentWorldPos;
   vec3 tangentCampos;
   vec3 tangentLightpos;
} vs_out;


void main()
{
    //tangent bitangent matrix calc
    vec3 T = normalize(vec3(modelMatrix * vec4(tangent, 0.0)));
    vec3 B = normalize(vec3(modelMatrix * vec4( cross(tangent, normal) , 0.0)));
    vec3 N = normalize(vec3(modelMatrix * vec4(normal, 0.0)));    
    mat3 TBN = transpose(mat3(T, B, N));

    vs_out.texCoord = texcoord;
    vs_out.tangentWorldPos = TBN * vec3(modelMatrix * vec4(pos, 0.0));
    vs_out.tangentCampos = camPos * TBN;
    vs_out.tangentLightpos = lightPos * TBN;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1);
}
