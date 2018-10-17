#version 410                                                                        
                                                                                    
layout (location = 0) in vec3 aPos;                                             
layout (location = 1) in vec3 aNormal;                                             
layout (location = 2) in vec3 aUV;                                               
                                                                                    
uniform mat4 projection;
uniform mat4 viewMatrix;
uniform mat4 viewExtentionMatrix;
uniform mat4 model;                                                              
                                                                                    
out vec2 TexCoords;                                                               
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = projection * viewMatrix * viewExtentionMatrix * model * vec4(aPos, 1.0);                                       
    TexCoords = vec2(aUV.x, aUV.y);                                                         
}
