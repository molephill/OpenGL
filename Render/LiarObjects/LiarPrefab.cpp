//
//  LiarPrefab.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/17.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "LiarPrefab.hpp"
#include "RenderMgr.hpp"

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
		m_shader = new Shader("E:/c++/VSOpenGL/OpenGL/Assets/Shaders/material.vs",
							  "E:/c++/VSOpenGL/OpenGL/Assets/Shaders/material.fs");
		m_texture1 = new LiarMaterial("E:/c++/VSOpenGL/OpenGL/Assets/Images/container2_specular.png", GL_RGBA);
		m_texture2 = new LiarMaterial("E:/c++/VSOpenGL/OpenGL/Assets/Images/container2.png", GL_RGBA);
#else
		m_shader = new Shader("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/material.vs",
							  "/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/material.fs");
		m_texture1 = new LiarMaterial1("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Images/container2_specular.png", GL_RGBA);
		m_texture2 = new LiarMaterial1("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Images/container2.png", GL_RGBA);
#endif // __APPLE__

		m_shader->Use();
		m_shader->SetInt("material.diffuse", 1);
		m_shader->SetInt("material.specular", 0);
    }
    
    void Cube::Render(Liar::RenderMgr* rmg, bool calcInvest)
    {
        float timeValue = Global::lastFrame;
        SetRotation(timeValue, timeValue, 0.0f);
        LiarObject::Render(rmg, calcInvest);

		m_texture1->Use(m_shader, GL_TEXTURE0);
		m_texture2->Use(m_shader, GL_TEXTURE1);

		DirectLight* mainLight = rmg->GetMainLight();
		mainLight->Use(m_shader);
        
//        float mixRate = (sin(timeValue)/2.0f) + 0.5f;
//        m_shader->SetFloat("mixRate", mixRate);
//        m_shader->SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
		m_shader->SetFloat("material.shininess", 64.0f);
		
        glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(m_vao);
    }
}
