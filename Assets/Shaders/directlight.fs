#version 410 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;
in vec3 ViewDir;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

// light params
struct DirectLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos; 
uniform vec3 objectColor;

uniform DirectLight light;
uniform Material material;

void main()
{
	vec3 norm = normalize(Normal);
 	
    // diffuse 
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    
    // specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(ViewDir, reflectDir), 0.0), material.shininess);
        
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
} 
