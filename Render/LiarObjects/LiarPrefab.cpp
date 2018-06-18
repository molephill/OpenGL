//
//  LiarPrefab.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/17.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "LiarPrefab.hpp"

namespace Liar
{
    Cube::Cube()
    {
        Upload();
    }
    
    void Cube::Upload()
    {
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
            
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
            
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
            
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,    0.0f, 1.0f
        };
        
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindVertexArray(m_vao);
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
#ifndef __APPLE__
        m_shader = new Shader("E:/c++/VSOpenGL/OpenGL/Assets/Shaders/base.vs",
                              "E:/c++/VSOpenGL/OpenGL/Assets/Shaders/base.fs");
        m_texture1 = new Texture2D("E:/c++/VSOpenGL/OpenGL/Assets/Images/wall.jpg");
        m_texture2 = new Texture2D("E:/c++/VSOpenGL/OpenGL/Assets/Images/awesomeface.png", GL_RGBA);
#else
        m_shader = new Shader("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/base.vs",
                              "/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/base.fs");
        m_texture1 = new Texture2D("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Images/wall.jpg");
        m_texture2 = new Texture2D("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Images/awesomeface.png", GL_RGBA);
#endif // __APPLE__
        
        m_shader->Use();
        m_shader->SetInt("texture1", 0);
        m_shader->SetInt("texture2", 1);
    }
    
    void Cube::Render(Camera* camera)
    {
        LiarObject::Render(camera);
        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}