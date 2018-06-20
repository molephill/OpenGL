//
//  LiarObject.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/16.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "LiarObject.hpp"
#include "RenderMgr.hpp"

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

	void LiarObject::SetScale(float v)
	{
		if (m_scale->SetValue(v, v, v))
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

	bool LiarObject::CalcMatrix(Liar::RenderMgr* rmg, bool calcInvest)
	{
		if (m_isDirty)
		{
			Camera* camera = rmg->GetCamera();
			glm::mat4& viewMatrix = camera->GetViewMatrix();

			LiarUtil::RestMatrix(m_matrix);
			m_matrix = glm::translate(m_matrix, m_position->GetValue());
			m_matrix = glm::scale(m_matrix, m_scale->GetValue());
			Global::SetVecX(1.0f);
			m_matrix = glm::rotate(m_matrix, m_rotation->GetX(), Global::commonVec3);
			Global::SetVecY(1.0f);
			m_matrix = glm::rotate(m_matrix, m_rotation->GetY(), Global::commonVec3);
			Global::SetVecZ(1.0f);
			m_matrix = glm::rotate(m_matrix, m_rotation->GetZ(), Global::commonVec3);

			if (calcInvest)
			{
				// calc world invest
				//m_investMatrix = glm::inverse(m_matrix);

				// calc view invest
				m_investMatrix = glm::inverse(viewMatrix * m_matrix);
			}

			m_isDirty = false;

			return true;
		}

		return false;
	}

	void LiarObject::SetBaseMatrix(Liar::RenderMgr* rmg, bool calcInvest)
	{
		CalcMatrix(rmg, calcInvest);

		Camera* camera = rmg->GetCamera();
		m_shader->Use();
		m_shader->SetMat4("model", m_matrix);
		m_shader->SetMat4("projection", camera->GetPerspective());
		m_shader->SetMat4("view", camera->GetViewMatrix());
	}
    
    void LiarObject::Render(Liar::RenderMgr* rmg, bool calcInvest)
    {
		SetBaseMatrix(rmg, calcInvest);
		if (calcInvest)
		{
			m_shader->SetMat4("invest", m_investMatrix);
		}

		Camera* camera = rmg->GetCamera();
		Light* light = rmg->GetMainLight();
		m_shader->SetVec3("lightColor", light->GetColor());
		m_shader->SetVec3("lightPos", light->GetViewPos());
		m_shader->SetVec3("viewPos", camera->GetPosition());
		m_shader->SetFloat("ambientStrength", light->GetAmbientStrength());
		m_shader->SetFloat("specularStrength", light->GetSpecularStrength());
		m_shader->SetInt("specularShininess", light->GetSpecularShininess());
    }
    
}
