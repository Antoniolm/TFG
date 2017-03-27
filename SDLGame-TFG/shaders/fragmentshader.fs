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
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;
in vec4 FragPosLightSpace;

// Uniform
uniform DirLight dirLight;
uniform Material material;
uniform vec3 viewPos;
uniform int invertNormal;
uniform int noLight;
uniform int numActivateLight;
uniform PointLight pointLights[numLight];
uniform bool normalMapping;

uniform sampler2D ourTexture;
uniform sampler2D normalMap; 
uniform sampler2D shadowMap; 

//Definition of functions
vec3 calculateDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float calculateShadow(vec4 fragPosLightSpace,vec3 normal, vec3 lightDir);

void main()
{ 
 vec3 result;
 vec3 norm = normalize(Normal);

//Calculate color of our texture
 vec4 texColor = texture(ourTexture,TextCoord);
 if(texColor.a < 0.1)
    discard;

if(normalMapping){
    // Obtain normal from normal map in range [0,1]
    norm = texture(normalMap, TextCoord).rgb;
    // Transform normal vector to range [-1,1]
    norm = normalize(norm * 2.0 - 1.0);

    // Get diffuse color
    vec3 color2 = texture(ourTexture, TextCoord).rgb;
    // Ambient
    vec3 ambient = color2;
    // Diffuse
    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * color2;
    // Specular
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;
    
    // Calculate shadow
    float shadow = calculateShadow(FragPosLightSpace,norm,lightDir);       
    vec3 lighting = (ambient + (0.8 - shadow) * (diffuse + specular)) * color2;

    color = vec4(lighting *( dirLight.ambient * material.ambient + diffuse * dirLight.diffuse * material.diffuse + specular * dirLight.specular * material.specular), 1.0f);   
}
else {
    //If is a object in the scene
     if(noLight==0){   
        vec3 viewDir = normalize(viewPos - FragPos);
     
        result = calculateDirLight(dirLight, norm, viewDir);

        for(int i = 0; i < numActivateLight; i++)
            result += calculatePointLight(pointLights[i], norm, FragPos, viewDir);  
           
        color =texColor * vec4(result, 1.0f);
        /*vec3 color2 = texture(ourTexture, TextCoord).rgb;
        vec3 normal = normalize(Normal);
        vec3 lightColor = vec3(1.0);
        // Ambient
        vec3 ambient = 0.15 * color2;
        // Diffuse
        vec3 lightDir = normalize(dirLight.direction - FragPos);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = diff * lightColor;
        // Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        float spec = 0.0;
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
        vec3 specular = spec * lightColor;    
        // Calculate shadow
        float shadow = calculateShadow(FragPosLightSpace,normal,lightDir);       
        vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color2; 
        
        color = vec4(lighting, 1.0f);*/
     }
     //If is a menu or text in the scene
     if(noLight==1)
        color=texColor* vec4(material.ambient,1.0f);
 }

}

vec3 calculateDirLight(DirLight light,vec3 normal,vec3 viewDir){
    vec3 lightDir = normalize(-light.direction);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    vec3 halfwayDir = normalize(lightDir +viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

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
    vec3 halfwayDir = normalize(lightDir +viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

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

float calculateShadow(vec4 fragPosLightSpace,vec3 normal, vec3 lightDir)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Check whether current frag pos is in shadow
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);   
        
    // Check whether current frag pos is in shadow
    //PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x){
        for(int y = -1; y <= 1; ++y)    {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    if(projCoords.z>1.0)
        shadow=0.0;

    return shadow;
}