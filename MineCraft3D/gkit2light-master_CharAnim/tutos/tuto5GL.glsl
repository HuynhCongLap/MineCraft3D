
//! \file tuto5GL.glsl

#version 330

#ifdef VERTEX_SHADER

layout(location= 0) in vec3 position;
layout (location=1) in vec2 texcoord;
layout (location=2) in vec3 normal;
layout(location= 3) in vec3 pos;

uniform mat4 mvpMatrix;

uniform float Globaltime;

out vec2 vertex_texcoord;
out vec2 height;

out vec3 FragPos; 
out vec3 Anormal;

void main( )
{
    height = vec2(sin((Globaltime/1000.0)+ pos.x),pos.y);
    vec3 position1 = position+pos  ;
    if(height.y <0.5)
	position1 += vec3(0.0,1 + sin((Globaltime/1000.0)+ pos.x),0.0);
    gl_Position= mvpMatrix * vec4(position1, 1);
    vertex_texcoord= texcoord;
    FragPos = position1;
    Anormal = normal;
}
#endif


#ifdef FRAGMENT_SHADER

in vec2 vertex_texcoord;
in vec2 height;

in vec3 FragPos; 
in vec3 Anormal;

uniform sampler2D ice_texture;
uniform sampler2D water_texture;
uniform sampler2D land_texture;
uniform sampler2D mou_texture;
uniform sampler2D top_texture;
uniform sampler2D grass_side_texture;
uniform sampler2D top_grass;
out vec4 fragment_color;

uniform vec3 lightPos;
uniform vec3 light1Pos;
uniform vec3 viewPos;

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
   
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient ;
    vec3 diffuse = light.diffuse * diff ;

    ambient *= attenuation;
    diffuse *= attenuation;
    return (ambient + diffuse );
}


void main()
{
   
     vec3 lightColor = vec3(1,1,1);
     float ambientStrength = 0.1;
     vec3 ambient = ambientStrength * lightColor; // ambient light

     vec3 norm = normalize(Anormal);
     vec3 lightDir = normalize(lightPos - FragPos);
     vec3 viewDir = normalize(viewPos - FragPos);
     
     float diff = max(dot(norm, lightDir), 0.0);
     vec3 diffuse = diff * lightColor; // diffuse light
     
     PointLight light;
     light.position = light1Pos;
     light.constant = 1.0;
     light.linear = 0.022;
     light.quadratic = 0.0019;
     light.ambient = vec3(0.9, 0.9, 0.9);
     light.diffuse = vec3(0.8, 0.8, 0.8);
     light.specular = vec3(1.0, 1.0, 1.0);
     vec3 cor = CalcPointLight(light,Anormal,FragPos,viewDir);
     vec3 cor1 = cor*vec3(1.0,0.0,0.3);
   
    vec4 phong = vec4(ambient + diffuse,1.0)+ vec4(cor1,1.0);
    vec4 color;
    float slope = 1.0 - Anormal.y;
    if(height.y < 0.5){  
     	color= texture(ice_texture, vertex_texcoord);
	color.z += height.x/50.0;
	color.y += height.x/50.0;
	color.x += height.x/50.0;
	fragment_color= phong*color ;
	return;
	}
    if(height.y > 0.5 && height.y <= 2.5){
	color= texture(land_texture, vertex_texcoord);
	fragment_color= phong*color;
	return;
	}
    if(height.y >2.5 && height.y <=6.5 && slope < 0.01){
	color= texture(mou_texture, vertex_texcoord);
	fragment_color= phong*color;
	return;
	}
    if(height.y >2.5 && height.y <=6.5 && slope > 0.5){
	color= texture(grass_side_texture, vertex_texcoord);
	fragment_color= phong*color;
	return;
	}
    if(height.y > 6.5 && height.y <=12.5 && slope < 0.01){
	color= texture(top_grass, vertex_texcoord);
	fragment_color= phong*color;
	return;
	}
      if(height.y > 6.5 && height.y <=12.5 && slope > 0.01){
	color= texture(top_texture, vertex_texcoord);
	fragment_color= phong*color;
	return;
	}
    if(height.y > 13.0 - 0.5){
     	color= texture(water_texture, vertex_texcoord);
	}

    fragment_color= phong*color;
    return;
}


#endif
