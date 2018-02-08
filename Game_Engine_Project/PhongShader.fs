#version 330 core
out vec4 fragColor;
in vec3 vertcolor;
in vec2 texcoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	fragColor = mix(texture(texture1, texcoord), texture(texture2, texcoord), 0.5);// * vec4(vertcolor, 1.0);
	//fragColor = texture(texture1, texcoord) * vec4(vertcolor, 1.0);
}
