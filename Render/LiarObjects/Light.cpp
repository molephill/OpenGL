//
//  Light.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/17.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "Light.hpp"
#include "RenderMgr.hpp"

namespace Liar
{
    DirectLight::DirectLight()
		:m_ambient(glm::vec3(0.2f)), m_diffuse(glm::vec3(0.5f))
		, m_specular(glm::vec3(32.0f)), m_color(glm::vec3(1.0f, 1.0f, 1.0f))
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
    
    DirectLight::~DirectLight()
    {
        
    }

	void DirectLight::SetColor(float r, float g, float b)
	{
		m_color.x = r;
		m_color.y = g;
		m_color.z = b;
	}

	bool DirectLight::CalcMatrix(Liar::RenderMgr* rmg, bool calcInvest)
	{
		if (LiarObject::CalcMatrix(rmg, calcInvest))
		{
			Camera* camera = rmg->GetCamera();
			m_viewPos = glm::vec3(camera->GetViewMatrix() * glm::vec4(m_position->GetValue(), 1.0));
			return true;
		}
		else
		{
			return false;
		}
	}

	void DirectLight::Use(Shader* shader)
	{
		/*shader->SetVec3("light.position", m_viewPos);
		shader->SetVec3("light.ambient", m_ambient.r*m_color);
		shader->SetVec3("light.diffuse", m_diffuse.r*m_color);
		shader->SetVec3("light.specular", m_specular.r*m_color);*/

		shader->SetVec3("light.position", m_viewPos);
		shader->SetVec3("light.ambient", m_ambient*m_color);
		shader->SetVec3("light.diffuse", m_diffuse*m_color);
		shader->SetVec3("light.specular", m_specular*m_color);
	}
    
    void DirectLight::Render(Liar::RenderMgr* rmg, bool calcInvest)
    {
		LiarObject::SetBaseMatrix(rmg, calcInvest);

#ifdef RENDER_DEBUG
        glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(m_vao);
#endif
    }
    
#ifdef RENDER_DEBUG
    void DirectLight::SetBuffers(unsigned int vbo)
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
#endif

	// ====================================== point_light ==========================================
	PointLight::PointLight(float constant, float linear, float quadratic)
		:DirectLight()
		, m_constant(constant), m_linear(linear), m_quadratic(quadratic)
	{

	}

	// ====================================== spot_light ==========================================
	SpotLight::SpotLight(float constant, float linear, float quadratic, float cutOff, float outerCutOff)
		:PointLight(constant, linear, quadratic)
		, m_direction(glm::vec3(0.0f, 0.0f, 1.0f)), m_cutOff(cutOff), m_outerCutOff(outerCutOff)
	{

	}
    
}
