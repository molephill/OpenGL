//
//  LiarObject.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/16.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "LiarObject.hpp"
#include "Camera.hpp"

namespace Liar
{
    LiarObject::LiarObject():
        m_position(new CPosition())
        ,m_rotation(new CRotation())
        ,m_scale(new CScale())
        ,m_isDirty(true)
        ,m_vao(0), m_vbo(0)
        ,m_matrix(glm::mat4(1.0))
    {
        
    }
    
    LiarObject::LiarObject(float x, float y, float z):
        m_position(new CPosition(x, y, z))
        ,m_rotation(new CRotation())
        ,m_scale(new CScale())
        ,m_isDirty(true)
        ,m_vao(0), m_vbo(0)
        ,m_matrix(glm::mat4(1.0))
    {
        
    }
    
    LiarObject::~LiarObject()
    {
        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);
//        glDeleteBuffers(1, &m_EBO);
        
        delete m_shader;
        
        delete m_scale;
        delete m_position;
        delete m_rotation;
    }
    
    
    // ===================================================
    void LiarObject::SetPosition(const glm::vec3& pos)
    {
        if (m_position->SetValue(pos))
        {
            m_isDirty = true;
        }
    }
    
    void LiarObject::SetPosition(float x, float y, float z)
    {
        if (m_position->SetValue(x, y, z))
        {
            m_isDirty = true;
        }
    }
    
    // ===================================================
    void LiarObject::AddPosition(const glm::vec3& pos)
    {
        if(m_position->AddValue(pos))
        {
            m_isDirty = true;
        }
    }
    
    void LiarObject::AddPosition(float x, float y, float z)
    {
        if(m_position->AddValue(x, y, z))
        {
            m_isDirty = true;
        }
    }
    
    // ===================================================
    void LiarObject::SetRotation(const glm::vec3& r)
    {
        if (m_rotation->SetValue(r))
        {
            m_isDirty = true;
        }
    }
    
    void LiarObject::SetRotation(float x, float y, float z)
    {
        if (m_rotation->SetValue(x, y, z))
        {
            m_isDirty = true;
        }
    }
    
    // ===================================================
    void LiarObject::AddRotation(const glm::vec3& r)
    {
        if (m_rotation->AddValue(r))
        {
            m_isDirty = true;
        }
    }
    
    void LiarObject::AddRotation(float x, float y, float z)
    {
        if (m_rotation->AddValue(x, y, z))
        {
            m_isDirty = true;
        }
    }
    
    // ===================================================
    void LiarObject::SetScale(const glm::vec3& r)
    {
        if (m_scale->SetValue(r))
        {
            m_isDirty = true;
        }
    }
    
    void LiarObject::SetScale(float x, float y, float z)
    {
        if (m_scale->SetValue(x, y, z))
        {
            m_isDirty = true;
        }
    }
    
    // ===================================================
    void LiarObject::AddScale(const glm::vec3& r)
    {
        if (m_scale->AddValue(r))
        {
            m_isDirty = true;
        }
    }
    
    void LiarObject::AddScale(float x, float y, float z)
    {
        if (m_scale->AddValue(x, y, z))
        {
            m_isDirty = true;
        }
    }
    
    void LiarObject::Upload()
    {
        
    }
    
    void LiarObject::Render(Camera* camera)
    {
//        if(m_isDirty)
//        {
//            glm::mat4 transform(1.0);
//            m_matrix = glm::translate(transform, m_position->GetValue());
////            m_matrix = glm::scale(m_matrix, m_scale->GetValue());
//            m_matrix = glm::rotate(m_matrix, 1.0f, m_rotation->GetValue());
//            m_isDirty = false;
//        }
        
        float timeValue = glfwGetTime();
        glm::mat4 transform(1.0);
//        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, timeValue, glm::vec3(1.0f, 0.0f, 0.0f));
        
        m_shader->Use();
        m_shader->SetMat4("projection", camera->GetMatrix()*transform);
    }
    
}
