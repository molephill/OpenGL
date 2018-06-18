//
//  RenderMgr.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "RenderMgr.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Liar
{
	RenderMgr::RenderMgr()
	{
		m_camera = new Camera(0.0f, 0.0f, 3.0f);
        m_mainLight = new Light();
		glEnable(GL_DEPTH_TEST);
	}

    RenderMgr::~RenderMgr()
    {
        delete m_mainLight;
		delete m_camera;
    }
    
    void RenderMgr::Init()
    {
//        m_render = new RenderItem();
//        m_render->Init();
        m_cube = new Cube();
//#ifdef DEBUG
//        m_mainLight->SetBuffers(m_cube->GetVBO());
//#endif
    }

	void RenderMgr::SetSize(unsigned int w, unsigned int h)
	{
		m_camera->SetSize(w, h);
		glViewport(0, 0, w, h);
	}
    
    void RenderMgr::Render()
    {
#ifdef RENDER_MOD_LINE
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
		// 先计算视角
		m_camera->Render();
        
        m_mainLight->Render(m_camera);
        
        m_cube->Render(m_camera);
        
    }
}
