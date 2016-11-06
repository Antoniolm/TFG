#version 330 core
out vec4 color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
  
in vec3 Normal;
in vec3 FragPos;  

uniform Light light;  
uniform Material material;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
 // Ambient
 vec3 ambient = lightColor * material.ambient;

 // Diffuse 
 vec3 norm = normalize(Normal);
 //vec3 lightDir = normalize(lightPos);
 //float diff = max(dot(norm, lightDir), 0.0);
 //vec3 diffuse = lightColor * (diff * material.diffuse);
  
 // Specular
 //vec3 viewDir = normalize(viewPos - FragPos);
 //vec3 reflectDir = reflect(-lightDir, norm);  
 //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
 //vec3 specular = lightColor * (spec * material.specular);  
       
 vec3 result = ambient; //+ diffuse + specular;
 color = vec4(result, 1.0f);

}