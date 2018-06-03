//
//  BaseShader.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "BaseShader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log.hpp"

void BaseShader::Init()
{
    InitVertexShader();
    InitFragmentShader();
    Link();
    Release();
}

void BaseShader::InitVertexShader()
{
    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShader, 1, &m_vertexShaderSource, nullptr);
    glCompileShader(m_vertexShader);
    
#ifdef DEBUG
    glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &m_succuss);
    if(!m_succuss)
    {
        glGetShaderInfoLog(m_vertexShader, DEFAULT_BUFF_SIZE, nullptr, m_infoLog);
//        LOG2("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n", m_infoLog);
         fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_VERTEX_SHADER, m_infoLog);
    }
#endif
}

void BaseShader::InitFragmentShader()
{
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShader, 1, &m_fragmentShaderSource, nullptr);
    glCompileShader(m_fragmentShader);
    
#ifdef DEBUG
    glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &m_succuss);
    if(!m_succuss)
    {
        glGetShaderInfoLog(m_fragmentShader, DEFAULT_BUFF_SIZE, nullptr, m_infoLog);
//        LOG2("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n", m_infoLog);
    }
#endif
}

void BaseShader::Link()
{
    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_vertexShader);
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glLinkProgram(m_shaderProgram);
    
#ifdef DEBUG
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &m_succuss);
    if(!m_succuss)
    {
        glGetProgramInfoLog(m_shaderProgram, DEFAULT_BUFF_SIZE, nullptr, m_infoLog);
//        LOG2("ERROR::SHADER::PROGRAM::LINKING_FAILED\n", m_infoLog);
    }
#endif
}

void BaseShader::Release()
{
    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
    m_vertexShader = 0;
    m_fragmentShader = 0;
}
