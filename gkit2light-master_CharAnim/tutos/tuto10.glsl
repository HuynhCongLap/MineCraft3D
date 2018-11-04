
#version 330

#ifdef VERTEX_SHADER
uniform mat4 mvpMatrix;

layout(location= 0) in vec3 position;
layout (location=1) in vec2 aTexCoord;


layout(location= 4) in vec3 color;

out vec3 p_color;
out vec2 TexCoord;
void main( )
{
    vec3 position1 = position+pos;
    p_color = color;
    TexCoord = aTexCoord;
    gl_Position=  mvpMatrix* vec4(position1, 1);
}

#endif


#ifdef FRAGMENT_SHADER

out vec4 FragColor;

in vec3 p_color;
in vec2 TexCoord;

uniform sampler2D texture0;
void main( )
{
    FragColor = texture(texture0, TexCoord);
}

#endif
