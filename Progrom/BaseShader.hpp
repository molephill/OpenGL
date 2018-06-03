//
//  BaseShader.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef BaseShader_hpp
#define BaseShader_hpp

#include <stdio.h>
#include "Define.h"

class BaseShader
{
public:
    BaseShader():m_vertexShader(0),m_fragmentShader(0),m_shaderProgram(0)
    {
    }
    
private:
    int m_vertexShader;
    int m_fragmentShader;
    int m_shaderProgram;
    
#ifdef DEBUG
    int m_succuss;
    char m_infoLog[DEFAULT_BUFF_SIZE];
#endif
    
    const char *m_vertexShaderSource = "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
    const char *m_fragmentShaderSource = "#version 410 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
    
public:
    void Init();
    int GetProgrom() { return m_shaderProgram; };
    
private:
    void InitVertexShader();
    void InitFragmentShader();
    void Link();
    void Release();
    
};

#endif /* BaseShader_hpp */
