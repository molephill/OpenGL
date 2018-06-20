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
    class Light:public LiarObject
    {
    public:
        Light();
        ~Light();

	private:
		float m_ambientStrength;
		float m_specularStrength;
		int m_specularShininess;
		glm::vec3 m_color;

		// view pos
		glm::vec3 m_viewPos;

	public:
		void SetColor(float, float, float);
		void SetColor(const glm::vec3& v) { m_color = v; };
		void SetAmbientStrength(float v) { m_ambientStrength = v; };
		void SetSpecularStrength(float v) { m_specularStrength = v; };
		void SetSpecularShininess(unsigned int v) { m_specularShininess = v; };

		glm::vec3& GetColor() { return m_color; };
		float GetAmbientStrength() { return m_ambientStrength; };
		float GetSpecularStrength() { return m_specularStrength; };
		int GetSpecularShininess() { return m_specularShininess; };

		// get view_pos
		glm::vec3& GetViewPos() { return m_viewPos; };
        
    public:
		virtual bool CalcMatrix(Liar::RenderMgr*, bool);
        virtual void Render(Liar::RenderMgr*, bool calcInvest = false);
        // show
#ifdef RENDER_DEBUG
        void SetBuffers(unsigned int);
#endif
    };
}

#endif /* Light_hpp */
