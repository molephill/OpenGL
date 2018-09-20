//
//  OpenGLWindow.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/19.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "OpenGLWindow.hpp"
#include "Log.hpp"
#include "Global.hpp"

namespace Liar
{
	OpenGLWindow::OpenGLWindow():m_renderMgr(nullptr)
	{
	}
    
    OpenGLWindow::OpenGLWindow(std::string title, unsigned int w, unsigned int h)
        :Liar::BaseWindow(title, w, h),
		m_renderMgr(nullptr)
    {
        
    }

	OpenGLWindow::~OpenGLWindow()
	{
		m_renderMgr = nullptr;
	}

	bool OpenGLWindow::Created()
	{

//#ifdef DEBUG
//        std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << std::endl;
//        std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
//        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
//        std::cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
//#endif

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		return true;
	}

	void OpenGLWindow::SetSize(unsigned int w, unsigned int h)
	{
		if (m_renderMgr)
		{
			m_renderMgr->SetSize(w, h);
		}
	}

	void OpenGLWindow::Render()
	{
		if (m_renderMgr)
		{
			m_renderMgr->Render();
		}
	}

	void OpenGLWindow::KeyInputEvent()
	{
        BaseWindow::KeyInputEvent();
        if(!m_renderMgr) return;
        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        {
            m_renderMgr->GetMainCamera()->AddY(Global::cameraMoveSpeed);
        }
        else if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        {
			m_renderMgr->GetMainCamera()->AddX(-Global::cameraMoveSpeed);
        }
        else if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        {
           m_renderMgr->GetMainCamera()->AddY(-Global::cameraMoveSpeed);
        }
        else if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_renderMgr->GetMainCamera()->AddX(Global::cameraMoveSpeed);
        }
	}

	bool OpenGLWindow::MouseEvent(double x, double y)
	{
        bool inWindow = BaseWindow::MouseEvent(x, y);
		int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
        if(inWindow)
        {
			if (state == GLFW_PRESS)
			{
				if (m_isFirstMouse)
				{
					m_isFirstMouse = false;
				}
				else
				{
					double offsetx = x - m_lastMouseX;
					double offsety = y - m_lastMouseY;

					offsetx *= Global::mouseSensitivity;
					offsety *= Global::mouseSensitivity;

					m_renderMgr->GetMainCamera()->RotateCamera(offsety, offsetx);
				}
				m_lastMouseY = y;
				m_lastMouseX = x;
			}
			else
			{
				m_isFirstMouse = true;
			}
        }
        return inWindow;
	}

	void OpenGLWindow::ScrollEvent(double offsetx, double offsety)
	{
       // Camera* mainCamera = m_renderMgr->GetCamera();
       // mainCamera->AddFov(-offsety);
		m_renderMgr->GetMainCamera()->ZoomCamera(-offsety);
	}
}
