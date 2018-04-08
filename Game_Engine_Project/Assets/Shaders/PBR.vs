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

out VS_OUT
{
    vec2 texCoord;
    vec3 tangentWorldPos;
    vec3 tangentCampos;
    vec3 tangentNormal;
    vec3 lightArray[5];
    vec3 lightColorArray[5];
} vs_out;



void main()
{
    //tangent bitangent matrix calc
    vec3 T = normalize(vec3(modelMatrix * vec4(tangent, 0.0)));
    vec3 N = normalize(vec3(modelMatrix * vec4(normal, 0.0)));

    //re-orthagonalize the tangent with the surface normal
    T = normalize(T - dot(T, N) * N);

    vec3 B = normalize(vec3(modelMatrix * vec4( cross(tangent, normal) , 0.0)));
    mat3 TBN = transpose(mat3(T, B, N));

    vs_out.texCoord = texcoord;
    vs_out.tangentWorldPos = TBN * vec3(modelMatrix * vec4(pos, 1.0));
    vs_out.tangentCampos = TBN * camPos;
    vs_out.tangentNormal = TBN * normal;

    vs_out.lightArray[0] = TBN * vec3(6, 3, -6);
    vs_out.lightArray[1] = TBN * vec3(6, 3, 6);
    vs_out.lightArray[2] = TBN * vec3(-6, 3, -6);
    vs_out.lightArray[3] = TBN * vec3(-6, 3, 6);
    vs_out.lightColorArray[0] = vec3(23.47, 21.31, 20.79);
    vs_out.lightColorArray[1] = vec3(23.47, 21.31, 20.79);
    vs_out.lightColorArray[2] = vec3(23.47, 21.31, 20.79);
    vs_out.lightColorArray[3] = vec3(23.47, 21.31, 20.79);

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(pos, 1);
}
