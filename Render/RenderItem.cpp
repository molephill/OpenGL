//
//  RenderItem.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/27.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "RenderItem.hpp"
#include "math.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Liar
{
    RenderItem::~RenderItem()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
        
        delete m_shader;
        delete m_texture1;
        delete m_texture2;
    }
    
    void RenderItem::InitBase()
    {
        float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left
        };
        
        unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
        };
        
        glGenVertexArrays(1, &m_VAO);
        
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
        
        glBindVertexArray(m_VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
    
    void RenderItem::Init()
    {
        InitBase();

#ifndef __APPLE__
		m_shader = new Shader("E:/c++/VSOpenGL/OpenGL/Assets/Shaders/test.vs",
			"E:/c++/VSOpenGL/OpenGL/Assets/Shaders/test.fs");
		m_texture1 = new Texture2D("E:/c++/VSOpenGL/OpenGL/Assets/Images/wall.jpg");
		m_texture2 = new Texture2D("E:/c++/VSOpenGL/OpenGL/Assets/Images/awesomeface.png", GL_RGBA);
#else
		m_shader = new Shader("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/test.vs",
			"/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Shaders/test.fs");
		m_texture1 = new Texture2D("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Images/wall.jpg");
		m_texture2 = new Texture2D("/Users/maowei/Downloads/C++/OpenGL/OpenGL/Assets/Images/awesomeface.png", GL_RGBA);
#endif // __APPLE__
        
        m_shader->Use();
        m_shader->SetInt("texture1", 0);
        m_shader->SetInt("texture2", 1);
    }
    
    void RenderItem::Draw(Camera* camera)
    {
        m_texture1->Use(GL_TEXTURE0);
        m_texture2->Use(GL_TEXTURE1);
        m_shader->Use();
        //    m_shader->SetFloat("xOffset", 0.5f);
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue)/2.0f) + 0.5f;
        m_shader->SetFloat("greenChange", greenValue);

		m_shader->SetMat4("projection", camera->GetPerspective());
		m_shader->SetMat4("view", camera->GetViewMatrix());
        
        glm::mat4 transform(1.0);
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));
        m_shader->SetMat4("model", transform);
       glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        transform = glm::mat4(1.0);
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = sin(glfwGetTime());
        transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        m_shader->SetMat4("model", transform);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(m_VAO);
    }
}
