#version 330 core
out vec4 color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
  
#define numLight 2

// in vec3f 
in vec3 Normal;
in vec2 TextCoord;
in vec3 FragPos; 

// Uniform
uniform DirLight dirLight;
uniform Material material;
uniform vec3 viewPos;
uniform PointLight pointLights[numLight];

uniform sampler2D ourTexture;

//Definition of functions
vec3 calculateDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{ 
 vec3 norm = normalize(Normal);
 vec3 viewDir = normalize(viewPos - FragPos);
 
 vec3 result = calculateDirLight(dirLight, norm, viewDir);

 for(int i = 0; i < numLight; i++)
    result += calculatePointLight(pointLights[i], norm, FragPos, viewDir);  
       
 color =texture(ourTexture,TextCoord) * vec4(result, 1.0f);
}

vec3 calculateDirLight(DirLight light,vec3 normal,vec3 viewDir){
	vec3 lightDir = normalize(-light.direction);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);


    // Combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    
    return (ambient + diffuse + specular);

}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // Combine results
    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}