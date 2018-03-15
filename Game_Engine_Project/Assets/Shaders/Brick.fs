#version 330 core
in vec2 ftexcoord;
//in vec3 fnormal;

float x = 96.0;
float y = 96.0;

out vec4 fragcolor;

void main()
{
    //find texcoord decimal 
    //x
    float decimalx = ftexcoord.x - mod( ftexcoord.x , 1/x );
    float decmodx = mod(decimalx, (1/x)*6);
    //y
    float decimaly = ftexcoord.y - mod( ftexcoord.y , 1/y );
    float decmody = mod(decimaly, (1/y)*3);

    bool isblock = false;
    if(decmodx > 0 && decmody > 0)
    {
        isblock = true;
    }

    fragcolor = vec4(float(isblock) * 0.2, float(isblock) * 0.2, float(isblock) * 0.5, 1);
    
}