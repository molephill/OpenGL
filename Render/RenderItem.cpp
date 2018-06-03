//
//  RenderItem.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/27.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "RenderItem.hpp"
#include "math.h"

RenderItem::~RenderItem()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    
    delete m_shader;
}

void RenderItem::InitBase()
{
//    float vertices[] = {
//        0.5f,  0.5f, 0.0f,  // top right
//        0.5f, -0.5f, 0.0f,  // bottom right
//        -0.5f, -0.5f, 0.0f,  // bottom left
//        -0.5f,  0.5f, 0.0f   // top left
//    };
//
//    unsigned int indices[] = {  // note that we start from 0!
//        0, 1, 3,  // first Triangle
//        1, 2, 3   // second Triangle
//    };
//
//    glGenVertexArrays(1, &m_VAO);
//    glGenBuffers(1, &m_VBO);
//    glGenBuffers(1, &m_EBO);
//
//    glBindVertexArray(m_VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    float vertices[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };
    
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
}

void RenderItem::Init()
{
    InitBase();
    m_shader = new Shader("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/test.vs",
                          "/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/test.fs");
}

void RenderItem::Draw()
{
    m_shader->Use();
//    m_shader->SetFloat("xOffset", 0.5f);
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue)/2.0f) + 0.5f;
    m_shader->SetFloat("greenChange", greenValue);
    glBindVertexArray(m_VAO);
}
