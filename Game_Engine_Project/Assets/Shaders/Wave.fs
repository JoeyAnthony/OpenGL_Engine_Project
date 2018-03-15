#version 330

in vec3 fnormal;
in vec2 ftexcoord;
in float ftime;

uniform sampler2D s_texture;

out vec4 glfragcolor;

void main() 
{   
  glfragcolor = texture2D(s_texture, ftexcoord);
}