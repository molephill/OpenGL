//
//  Light.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/17.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "Light.hpp"

namespace Liar
{
    Light::Light()
    {
        
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);
        
#ifndef __APPLE__
        m_shader = new Shader("E:/c++/VSOpenGL/OpenGL/Assets/Shaders/light.vs",
                              "E:/c++/VSOpenGL/OpenGL/Assets/Shaders/light.fs");
#else
        m_shader = new Shader("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/light.vs",
                              "/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/light.fs");
#endif // __APPLE__
    }
    
    Light::~Light()
    {
        
    }
    
    void Light::Render(Liar::Camera* camera)
    {
#ifdef DEBUG
        LiarObject::Render(camera);
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
#endif
        
        m_shader->SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
        m_shader->SetVec3("lightColor",  1.0f, 1.0f, 1.0f);
    }
    
#ifdef DEBUG
    void Light::SetBuffers(unsigned int vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
#endif
    
}
