
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
    Normal = vec3(model*vec4(aNormal,0.0));
    
}

#endif


#ifdef FRAGMENT_SHADER

out vec4 fragment_color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float materialShininess;

in vec3 FragPos;  
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;
float specularStrength = 0.5;

void main( )
{

     
     vec3 ambient = lightColor * materialAmbient;  // ambient light

     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(lightPos - FragPos);
     
     float diff = max(dot(norm, lightDir), 0.0);
     vec3 diffuse = lightColor * (diff * materialDiffuse); // diffuse light

     //vec3 result = (ambient + diffuse) * objectColor;
     //vec3 result  = 	ambient * objectColor;
 
     vec3 viewDir = normalize(viewPos - FragPos);
     vec3 reflectDir = reflect(-lightDir, norm);
     float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
     vec3 specular = lightColor * (spec * materialSpecular);
 
     ambient = vec3(0.2f, 0.2f, 0.2f) * ambient;
     diffuse = vec3(0.5f, 0.5f, 0.5f) * diffuse;
     specular = vec3(1.0f, 1.0f, 1.0f)* specular;
     vec3 result = ambient + diffuse + specular;
     fragment_color = vec4(result, 1.0);
}

#endif
