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
        m_shader = new Shader("E:/c++/VSOpenGL/OpenGL/Assets/Shaders/base.vs",
                              "E:/c++/VSOpenGL/OpenGL/Assets/Shaders/base.fs");
#else
        m_shader = new Shader("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/base.vs",
                              "/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/base.fs");
#endif // __APPLE__
    }
    
    Light::~Light()
    {
        
    }
    
    void Light::Render(Liar::RenderMgr* rmg)
    {
		LiarObject::Render(rmg);
#ifdef DEBUG
        glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(m_vao);
#endif
    }
    
#ifdef DEBUG
    void Light::SetBuffers(unsigned int vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
#endif
    
}
