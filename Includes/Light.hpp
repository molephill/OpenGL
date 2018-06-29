//
//  Light.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/17.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include "LiarObject.hpp"

namespace Liar
{
    class DirectLight:public LiarObject
    {
    public:
        DirectLight();
        virtual ~DirectLight();

	protected:
		glm::vec3 m_color;
		// 
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;

		// view pos
		glm::vec3 m_viewPos;

	public:
		void SetColor(float, float, float);
		void SetColor(const glm::vec3& v) { m_color = v; };
		
		void SetAmbient(const glm::vec3& v) { m_ambient = v; };
		void SetAmbient(float r, float g, float b) { m_ambient.r = r; m_ambient.g = g; m_ambient.b = b; };

		void SetDiffuse(const glm::vec3& v) { m_diffuse = v; };
		void SetDiffuse(float r, float g, float b) { m_diffuse.r = r; m_diffuse.b = b; m_diffuse.b = b; };

		void SetSpecular(const glm::vec3& v) { m_specular = v; };
		void SetSpecular(float r, float g, float b) { m_specular.r = r; m_specular.g = g; m_specular.b = b;	};

		glm::vec3& GetColor() { return m_color; };
		glm::vec3& GetAmbient() { return m_ambient;	};
		glm::vec3& GetDiffuse() { return m_diffuse; };
		glm::vec3& GetSpecular() { return m_specular; };

		// get view_pos
		glm::vec3& GetViewPos() { return m_viewPos; };
        
    public:
		virtual bool CalcMatrix(Liar::RenderMgr*, bool);
		virtual void Use(Shader*);
        virtual void Render(Liar::RenderMgr*, bool calcInvest = false);
        // show
#ifdef RENDER_DEBUG
        void SetBuffers(unsigned int);
#endif
    };

	// ====================================== point_light ==========================================
	class PointLight :public DirectLight
	{
	public:
		PointLight(float constant = 1.0f, float linear = 0.09f, float quadratic = 0.032f);

	protected:
		float m_constant;
		float m_linear;
		float m_quadratic;
	};
}

#endif /* Light_hpp */
