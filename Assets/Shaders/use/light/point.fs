#version 410

const int MAX_POINT_LIGHTS = 2;

in vec2 TexCoord0;
in vec3 Normal0;                                                                 
                                                                                    
out vec4 FragColor;
                                                                                    
struct BaseLight
{                                                                     
    vec3 Color;                                                                  
    float Ambient;
    float Diffuse;
};

struct PointLight
{                                                                         
    BaseLight Base;
    vec3 Position;                                                                         
    float Constant;
    float Linear;
    float Exp;
};

uniform PointLight PointLights[MAX_POINT_LIGHTS];
uniform int NumPointLights;                               
uniform sampler2D gSampler;


vec4 CalcPointLight(int Index, vec3 Normal)
{                                                 
    vec3 LightDirection = WorldPos0 - PointLights[Index].Position;
    float Distance = length(LightDirection);                                                
    LightDirection = normalize(LightDirection);                                             
                                                                                            
    vec4 Color = CalcLightInternal(PointLights[Index].Base, LightDirection, Normal);       
    float Attenuation =  PointLights[Index].Atten.Constant +                               
                         PointLights[Index].Atten.Linear * Distance +                      
                         PointLights[Index].Atten.Exp * Distance * Distance;               
                                                                                            
    return Color / Attenuation;                                                             
}                                                       
                                                                                    
void main()                                                                         
{
    vec3 Normal = normalize(Normal0);                                                               
    vec4 TotalLight = vec4(0, 0, 0, 0);                                         
                                                                                            
    for (int i = 0 ; i < NumPointLights ; i++) {                                           
        TotalLight += CalcPointLight(i, Normal);                                            
    }                                                                                       
                                                                                            
    FragColor = texture2D(gSampler, TexCoord0.xy) * TotalLight;                                    
}
