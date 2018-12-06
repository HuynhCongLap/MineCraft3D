
#version 330

#ifdef VERTEX_SHADER

layout(location= 0) in vec3 position;
layout(location= 1) in vec3 color;
layout (location=2) in vec3 normal;
layout(location= 3) in vec3 pos;
uniform mat4 mvpMatrix;

out vec3 FragPos; 
out vec3 LightPos;
out vec3 Anormal;
out vec3 LightColor;
void main( )
{
    vec3 position1 = position+pos;
    FragPos = position1; 
    LightPos = pos;
    gl_Position= mvpMatrix * vec4(position1, 1);
    LightColor = color;
    Anormal = normal;
}

#endif


#ifdef FRAGMENT_SHADER

out vec4 FragColor;
in vec3 FragPos;
in vec3 LightPos;
in vec3 Anormal;
in vec3 LightColor;

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main( )
{
    PointLight light;
    light.position = LightPos;
    light.constant = 1.0;
    light.linear = 0.022;
    light.quadratic = 0.0019;
    light.ambient = vec3(0.9, 0.9, 0.9);
    light.diffuse = vec3(0.8, 0.8, 0.8);
    light.specular = vec3(1.0, 1.0, 1.0);

    vec3 cor = CalcPointLight(light,-Anormal,FragPos,vec3(1,1,1));
    vec3 cor1 = cor*LightColor;
    FragColor = vec4(cor1,1.0);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient ;
    vec3 diffuse = light.diffuse * diff ;
    vec3 specular = light.specular * spec;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}


#endif
