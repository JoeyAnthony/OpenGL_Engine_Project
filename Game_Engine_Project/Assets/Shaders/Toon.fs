//out vec4 fragcolor;
#version 330 core
in vec3 fnormal;
in vec3 fcampos;
in vec3 fpos;

float ambient = 0.3;
vec3 lightdir = normalize(vec3(1, 1, 1));
float factor = 50;

float toon(float num)
{
    float modulo = mod(num, 0.1);
    return num - modulo;
}

float toon(float num, float modu)
{
    float modulo = mod(num, modu);
    return num - modulo;
}

void main()
{
    float diffuse = 0.5 * dot(lightdir, normalize(fnormal));

    vec3 reflectvector = reflect(-lightdir, normalize(fnormal));
    float specular = pow( max(0.0, dot(reflectvector, normalize(fpos - fcampos) )), factor);

    float light = toon(ambient) + toon(diffuse, 0.18) + toon(specular, 0.3);
    gl_FragColor = vec4(light, light, light, 1);
}

