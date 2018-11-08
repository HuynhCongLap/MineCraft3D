
//! \file tuto9_texture1.glsl

#version 330

#ifdef VERTEX_SHADER
layout(location= 0) in vec3 position;
layout(location= 2) in vec3 aNormal;
uniform mat4 mvpMatrix;


uniform mat4 model;
out vec3 FragPos;  
out vec3 Normal;

void main( )
{
    gl_Position= mvpMatrix * vec4(position, 1);
    FragPos = vec3(model * vec4(position, 1.0));
    Normal = aNormal;
    
}

#endif


#ifdef FRAGMENT_SHADER

out vec4 fragment_color;

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 FragPos;  
in vec3 Normal;

uniform vec3 lightPos;

void main( )
{

     float ambientStrength = 0.1;
     vec3 ambient = ambientStrength * lightColor; // ambient light

     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(lightPos - FragPos);
     
     float diff = max(dot(norm, lightDir), 0.0);
     vec3 diffuse = diff * lightColor; // diffuse light

     vec3 result = (ambient + diffuse) * objectColor;
     //vec3 result  = 	ambient * objectColor;	
     fragment_color = vec4(result, 1.0);
}

#endif
