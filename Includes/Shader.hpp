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
#include <glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Define.h"
#include <Matrices.h>

namespace Liar
{
    
    // shader类型
    enum ShaderType
    {
        TYPE_VERTEXT = 0,
        TYPE_FRAGMENT = 1,
        TYPE_PROGROM = 2,
    };
    
    class Shader
    {
    public:
        Shader(const std::string&, const std::string&);
        Shader(const char* vertexPath, const char* fragmentPath);
        
    private:
        void Init(const char*, const char*);
        unsigned int m_ID;
        
    public:
        void Use();
        unsigned int GetID() { return m_ID; };
        // ------------------------------------------------------------------------
        void SetBool(const std::string&, bool value) const;
        // ------------------------------------------------------------------------
        void SetInt(const std::string&, int value) const;
        // ------------------------------------------------------------------------
        void SetFloat(const std::string&, float value) const;
        // ------------------------------------------------------------------------
        void SetVec2(const std::string&, const glm::vec2&) const;
        void SetVec2(const std::string&, float, float) const;
        // ------------------------------------------------------------------------
        void SetVec3(const std::string&, const glm::vec3&) const;
        void SetVec3(const std::string&, float, float, float) const;
        // ------------------------------------------------------------------------
        void SetVec4(const std::string&, const glm::vec4&) const;
        void SetVec4(const std::string&, float, float, float, float) const;
        // ------------------------------------------------------------------------
        void SetMat2(const std::string&, const glm::mat2&) const;
        // ------------------------------------------------------------------------
        void SetMat3(const std::string&, const glm::mat3&) const;
        // ------------------------------------------------------------------------
        void SetMat4(const std::string&, const glm::mat4&) const;
		void SetMat4(const std::string&, const Liar::Matrix4&) const;
        
    private:
        void CheckCompileErrors(unsigned int, ShaderType);
    };
}

#endif /* Shader_hpp */
