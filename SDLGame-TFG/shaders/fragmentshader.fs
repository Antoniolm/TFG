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
  
#define numLight 5

// in vec3f 
in vec3 Normal;
in vec2 TextCoord;
in vec3 FragPos; 

// Uniform
uniform DirLight dirLight;
uniform Material material;
uniform vec3 viewPos;
uniform int invertNormal;
uniform int noLight;
uniform int numActivateLight;
uniform PointLight pointLights[numLight];

uniform sampler2D ourTexture;

//Definition of functions
vec3 calculateDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{ 
 vec3 norm;
 vec3 result;
 /*if(invertNormal==1) norm = normalize(Normal);
 else norm = normalize(Normal);*/
 norm = normalize(Normal);

 //Calculate color of our texture
 vec4 texColor = texture(ourTexture,TextCoord);
 if(texColor.a < 0.1)
        discard;

//If is a object in the scene
 if(noLight==0){   
    vec3 viewDir = normalize(viewPos - FragPos);
 
    result = calculateDirLight(dirLight, norm, viewDir);

    for(int i = 0; i < numActivateLight; i++)
        result += calculatePointLight(pointLights[i], norm, FragPos, viewDir);  
       
    color =texColor * vec4(result, 1.0f);
 }
 //If is a menu or text in the scene
 if(noLight==1)
    color=texColor* vec4(material.ambient,1.0f);
 
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
    vec3 diffuse = light.diffuse * (diff * material.ambient);
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