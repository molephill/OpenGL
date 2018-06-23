#version 410 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;

// light params
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D texture1;
uniform sampler2D texture2;
  

uniform vec3 viewPos; 
uniform vec3 objectColor;

uniform float mixRate;

uniform Light light;

void main()
{
 	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.diffuse;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = light.specular * spec;  
        
    vec3 result = (light.ambient + diffuse + specular) * objectColor;
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixRate) * vec4(result, 1.0);
} 
