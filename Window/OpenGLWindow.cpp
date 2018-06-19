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
    
    OpenGLWindow::OpenGLWindow(std::string title, unsigned int w, unsigned int h)
        :Liar::BaseWindow(title, w, h)
    {
        
    }

	bool OpenGLWindow::Created()
	{

#ifdef DEBUG
//            cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << endl;
//            cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
//            cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
//            cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
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

	void OpenGLWindow::KeyInputEvent()
	{
        BaseWindow::KeyInputEvent();
        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        {
            m_renderMgr->GetCamera()->MoveForward(MOVE_DIRECTION::FORWARD);
        }
        else if(glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        {
            m_renderMgr->GetCamera()->MoveForward(MOVE_DIRECTION::RIGHT);
        }
        else if(glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        {
            m_renderMgr->GetCamera()->MoveForward(MOVE_DIRECTION::BACKWARD);
        }
        else if(glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_renderMgr->GetCamera()->MoveForward(MOVE_DIRECTION::LEFT);
        }
	}

	bool OpenGLWindow::MouseEvent(double x, double y)
	{
        bool inWindow = BaseWindow::MouseEvent(x, y);
		int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
        if(inWindow && state == GLFW_PRESS)
        {
            if(m_isFirstMouse)
            {
                m_isFirstMouse = false;
            }
            else
            {
                Camera* mainCamera = m_renderMgr->GetCamera();
                
                double offsetx = x - m_lastMouseX;
				double offsety = y - m_lastMouseY;
                
                offsetx *= Global::mouseSensitivity;
                offsety *= Global::mouseSensitivity;

                mainCamera->AddRotation(offsetx, offsety, 0.0f);
            }
            
            m_lastMouseY = y;
            m_lastMouseX = x;
        }
        return inWindow;
	}

	void OpenGLWindow::ScrollEvent(double offsetx, double offsety)
	{
        Camera* mainCamera = m_renderMgr->GetCamera();
        mainCamera->AddFov(-offsety);
	}
}
