#version 410

const int MAX_SPOT_LIGHTS = 2;

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

struct SpotLight                                                                            
{                                                                                           
    PointLight Base;                                                                        
    vec3 Direction;                                                                         
    float Cutoff;                                                                           
};

uniform SpotLight SpoitLights[MAX_SPOT_LIGHTS];
uniform int NumSpoitLights;                               
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

vec4 CalcSpotLight(SpotLight l, vec3 Normal)                                                
{                                                                                           
    vec3 LightToPixel = normalize(WorldPos0 - l.Base.Position);                             
    float SpotFactor = dot(LightToPixel, l.Direction);                                      
                                                                                            
    if (SpotFactor > l.Cutoff) {                                                            
        vec4 Color = CalcPointLight(l.Base, Normal);                                     
        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - l.Cutoff));                   
    }                                                                                       
    else {                                                                                  
        return vec4(0,0,0,0);                                                               
    }                                                                                       
}                                                       
                                                                                    
void main()                                                                         
{
    vec3 Normal = normalize(Normal0);                                                               
    vec4 TotalLight = vec4(0, 0, 0, 0);                                         
                                                                                            
    for (int i = 0 ; i < NumSpoitLights ; i++) {                                           
        TotalLight += CalcSpotLight(i, Normal);                                            
    }                                                                                       
                                                                                            
    FragColor = texture2D(gSampler, TexCoord0.xy) * TotalLight;                                    
}
