
//! \file tuto5GL.glsl

#version 330

#ifdef VERTEX_SHADER

layout(location= 0) in vec3 position;
layout (location=1) in vec2 texcoord;
layout(location= 3) in vec3 pos;
uniform mat4 mvpMatrix;

out vec2 vertex_texcoord;
out vec2 height;
void main( )
{
    vec3 position1 = position+pos;
    gl_Position= mvpMatrix * vec4(position1, 1);
    height = vec2(0,pos.y);
    vertex_texcoord= texcoord;
}
#endif


#ifdef FRAGMENT_SHADER

in vec2 vertex_texcoord;
in vec2 height;

uniform sampler2D ice_texture;
uniform sampler2D water_texture;
uniform sampler2D land_texture;
uniform sampler2D mou_texture;
uniform sampler2D top_texture;

out vec4 fragment_color;

void main()
{
    vec4 color;

    if(height.y == 0)   
     	color= texture(ice_texture, vertex_texcoord);
    if(height.y > 0)
	color= texture(land_texture, vertex_texcoord);
    if(height.y >2)
	color= texture(mou_texture, vertex_texcoord);
    if(height.y > 7)
	color= texture(top_texture, vertex_texcoord);
    if(height.y > 12)
     color= texture(water_texture, vertex_texcoord);

    fragment_color= color;
}
#endif
