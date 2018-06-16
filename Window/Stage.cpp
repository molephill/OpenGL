#include "Stage.hpp"
#include "Global.hpp"

namespace Liar
{
    Stage::Stage():m_isActive(true)
	{
		m_windowActive = new WindowActiveMgr();
		m_openglWindow = new OpenGLWindow();
        m_openglWindow->Init("OpenGL");
        m_windowActive->RegisttHandler(m_openglWindow);
        
        Global::mainStage = this;
        Global::windowActive = m_windowActive;
        
        while(m_isActive)
        {
            float curFrame = glfwGetTime();
            Global::delataTime = curFrame - Global::lastFrame;
            Global::lastFrame = curFrame;
            
            m_windowActive->ProcessHandler();
            m_isActive = m_openglWindow->ProcessHandler();
        }
	}


	Stage::~Stage()
	{
		delete m_windowActive;
        delete m_openglWindow;
	}
}
