#version 410                                                                        
                                                                                    
layout (location = 0) in vec3 aPos;                                             
layout (location = 1) in vec3 aNormal;                                             
layout (location = 2) in vec3 aUV;   
layout (location = 3) in vec3 aColor;                                            
                                                                                    
uniform mat4 mvpTrans;
uniform mat4 model;                                                              
                                                                                    
out vec2 TexCoords;                                                               
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = mvpTrans * model * vec4(aPos, 1.0);                                       
    TexCoords = vec2(aUV.x, aUV.y);                                                         
}
