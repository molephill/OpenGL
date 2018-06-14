//
//  OpenGLWindow.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/19.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "OpenGLWindow.hpp"
#include "Log.hpp"

namespace Liar
{
	OpenGLWindow::OpenGLWindow()
	{
	}

	bool OpenGLWindow::Created()
	{

#ifdef DEBUG
		//    cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << endl;
		//    cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
		//    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
		//    cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
#endif

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		m_renderMgr = new RenderMgr();
		m_renderMgr->Init();

		return true;
	}

	void OpenGLWindow::SetSize(unsigned int w, unsigned int h)
	{
		m_renderMgr->SetSize(w, h);
	}

	void OpenGLWindow::Render()
	{
        m_renderMgr->Render();
	}
}
