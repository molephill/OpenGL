#include "Stage.hpp"
#include "Global.hpp"

namespace Liar
{
    Stage::Stage():m_isActive(true)
	{
		m_windowActive = new WindowActiveMgr();

		m_openglMainWindow = new OpenGLWindow();
        m_openglMainWindow->Init("LiarMainOpenGL");

		m_renderMgr = new RenderMgr();
		m_openglMainWindow->SetRenderMgr(m_renderMgr);

        m_windowActive->RegisttHandler(m_openglMainWindow);
        
        Global::mainStage = this;
        Global::windowActive = m_windowActive;
        
        while(m_isActive)
        {
            float curFrame = static_cast<float>(glfwGetTime());
            Global::delataTime = curFrame - Global::lastFrame;
            Global::lastFrame = curFrame;
            
            m_windowActive->ProcessHandler();
            m_isActive = m_openglMainWindow->ProcessHandler();
        }
	}


	Stage::~Stage()
	{
		delete m_windowActive;
        delete m_openglMainWindow;
	}
}
