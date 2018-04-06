#version 330 core
out vec4 fragcolor;
//in variables
in VS_OUT
{
   vec2 texCoord;
   vec3 tangentPos;
   vec3 tangentCampos;
   vec3 tangentLightpos;
} vs_in;

//texture samplers
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;


float ambient = 0;
float factor = 4;


void main()
{
    //calculate normal from texture
    vec3 normal = texture2D(texture_normal1, vec2(vs_in.texCoord.x, 1-vs_in.texCoord.y)).rgb;
    normal = normalize(normal * 2 - 1);


    //get diffuse colors
    vec4 diffuse = texture2D(texture_height1, vec2(vs_in.texCoord.x, 1-vs_in.texCoord.y));

    //reflect
    vec3 reflectvector = reflect(-vs_in.tangentLightpos, normalize(normal));

    //specular intensity en texture samenvoegen
    float specularintensity = pow( max(0.0, dot(reflectvector, normalize(vs_in.tangentPos - vs_in.tangentCampos) )), factor);
    vec4 specular = texture2D(texture_specular1, vec2(vs_in.texCoord.x, 1-vs_in.texCoord.y)) * specularintensity;

    vec4 ambient = vec4(0.35f, 0.64f, 0.99f, 1.0f) * (1-specularintensity/ factor);


    //mix diffuse and specualar
    vec4 halflight = mix(ambient, diffuse, 0.7);
    vec4 light = mix(halflight, specular, 0.5);


    vec4 color = light;
    fragcolor = color;
}