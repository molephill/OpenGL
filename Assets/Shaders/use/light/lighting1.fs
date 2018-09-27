#version 410 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct BaseLight {
    vec3 color;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight {
    BaseLight baseLight;
    vec3 direction;
};

struct PointLight {
    BaseLight baseLight;
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    PointLight pointLight;

    vec3 direction;
    float cutOff;
    float outerCutOff;       
};

#define NR_POINT_LIGHTS 4
#define NR_SPOT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform Material material;
uniform int numPointLights;
uniform int numSpotLights;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    // phase 2: point lights
    int num = min(NR_POINT_LIGHTS, numPointLights);
    for(int i = 0; i < num; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light
    num = min(NR_SPOT_LIGHTS, numSpotLights);
    for(int i = 0; i < num; i++)
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.baseLight.color * light.baseLight.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.baseLight.color * light.baseLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.baseLight.color * light.baseLight.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.baseLight.color * light.baseLight.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.baseLight.color * light.baseLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.baseLight.color * light.baseLight.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.pointLight.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.pointLight.position - fragPos);
    float attenuation = 1.0 / (light.pointLight.constant + light.pointLight.linear * distance + light.pointLight.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.pointLight.baseLight.color * light.pointLight.baseLight.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.pointLight.baseLight.color * light.pointLight.baseLight.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.pointLight.baseLight.color * light.pointLight.baseLight.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}