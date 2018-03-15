#version 330 core
out vec4 fragcolor;
//in variables
in VS_OUT
{
   vec2 texCoord;
   vec3 tangentWorldPos;
   vec3 tangentCampos;
   vec3 tangentLightpos;
} vs_in;

//texture samplers
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_normal1;
uniform sampler2D texture_normal2;
uniform sampler2D texture_height1;
uniform sampler2D texture_height2;


float ambient = 0;
float factor = 4;

 vec3 lightArray[];
 vec3 lightColorArray[];

const float PI = 3.14159265359;


//calculating reflectance
 vec3 frenelSchlick(float cosTheta, vec3 F0)
 {
     return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
 }

//indicate the amount of microfacets aligning with the halfwayvector
 float DistributionGGX(vec3 normal, vec3 halfwayvec, float roughness)
 {
    float Rough2 = roughness*roughness;
    float NdotH = dot(normal, halfwayvec);
    float NdotH2 = NdotH*NdotH;

    float denominator = NdotH2 *(Rough2-1) +1;
    denominator = PI * (denominator * denominator);

    return Rough2 / denominator;
 }

//calculate overshadowing(obstruction) of surface microfacets
 float GSchlickGGX(NdotV, float roughness)
 {
     float r = roughness+1;
     float kdirect = (r*r)/8;

     float schlick = NdotV/(NdotV*(1-kdirect) + kdirect);
 }
//Smith's method to take view obstruction and light obstruction both into account
float SmithGGX(vec3 normal, vec3 viewdir, vec3 lightdir, float roughness)
{
    float NdotV = max( dot( normal, viewdir), 0.0);
    float NdotL = max( dot( normal, lightdir), 0.0);
    gsub1 = GSchlickGGX(NdotV, roughness);
    gsub2 = GSchlickGGX(NdotL, roughness);

    return gsub1*gsub2;
}


void main()
{
    lightArray[0] = vs_in.tangentLightpos;
    lightColorArray[0] = vec3(23.47, 21.31, 20.79);

    //texture normal(N)
    vec3 normal = normalize(texture2D(texture_normal1, vec2(vs_in.texCoord.x, 1-vs_in.texCoord.y)).rgb);
    //light-out direction(V)
    vec3 LoDir = (vs_in.tangentCampos - vs_in.tangentWorldPos);
    normal = normalize(normal * 2 - 1);

    //radiance out
    vec3 Lo = vec3(0.0);
    //loop over lights
    for( int i = 0; i < 1; i++)
    {
        //light-in direction(L)
        vec3 LiDir = normalize(lightArray[i] - vs_in.tangentWorldPos);
        //halfway vector(H)
        vec3 halfwayVec =  normalize(LoDir + LiDir);

        float distance = length(lightArray[i] - vs_in.tangentWorldPos);

        //brightness
        float attenuation = 1.0/(distance * distance);
        vec3 radiance = lightColorArray[i] * attenuation; //andere attenuation misschien(meer controle?)
    

        ////Calculating Cook-Torrace specular BRDF////
        //reflectance at zero incidence, base reflectance
        //simplified assumption that most dialectric surfaces have a visually correct base reflectance of 0.04
        vec3 F0 = vec3(0.04);
        //the more metallic, the more albedo color
        F0 = mix(F0, albedo, metallic); //NO METALLIC
        vec3 reflectanceRatio = frenelSchlick( max( dot(LoDir, halfwayVec), 0.0), F0);
        float normaldistribution = DistributionGGX(normal, halfwayVec, roughness); //NO ROUGHNESS
        float obstruction = (normal, LoDir, )

    }


    ///////////////////////////////////////////////////////////////////////

    //     //calculate normal from texture
    //     vec3 normal = texture2D(texture_normal1, vec2(vs_in.texCoord.x, 1-vs_in.texCoord.y)).rgb;
    //     normal = normalize(normal * 2 - 1);


    //     //get diffuse colors
    //     vec4 diffuse = texture2D(texture_height1, vec2(vs_in.texCoord.x, 1-vs_in.texCoord.y));

    //     //reflect
    //     vec3 reflectvector = reflect(-vs_in.tangentLightpos, normalize(normal));

    //     //specular intensity en texture samenvoegen
    //     float specularintensity = pow( max(0.0, dot(reflectvector, normalize(vs_in.tangentWorldPos - vs_in.tangentCampos) )), factor);
    //     vec4 specular = texture2D(texture_specular1, vec2(vs_in.texCoord.x, 1-vs_in.texCoord.y)) * specularintensity;

    //     vec4 ambient = vec4(0.35f, 0.64f, 0.99f, 1.0f) * (1-specularintensity/ factor);


    //     //mix diffuse and specualar
    //     vec4 halflight = mix(ambient, diffuse, 0.7);
    //     vec4 light = mix(halflight, specular, 0.5);


    //     vec4 color = light;
    //     fragcolor = color;
}