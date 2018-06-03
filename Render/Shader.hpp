//
//  Shader.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/3.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Define.h"

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    
private:
    unsigned int m_ID;
    
public:
    void Use();
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    
private:
    void CheckCompileErrors(unsigned int, ShaderType);
};

#endif /* Shader_hpp */
