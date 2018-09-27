#version 410
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;

struct BaseLight
{
    vec3 color;
    float ambient;
    float diffuse;
}

struct DirectionalLight
{
    BaseLight baseLight;
    vec3 position;
}
  
uniform DirectionalLight directionalLight;
uniform vec3 viewPos; 
uniform vec3 objectColor;

void main()
{
    // ambient
    vec3 ambient = directionalLight.ambient * directionalLight.baseLight.color;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(directionalLight.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse =  directionalLight.baseLight.diffuse * diff * directionalLight.baseLight.color;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * directionalLight.baseLight.color;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
} 
