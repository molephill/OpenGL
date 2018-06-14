#include "Stage.hpp"

namespace Liar
{
    Stage::Stage():m_isActive(true)
	{
		windowActive = new WindowActiveMgr();
		m_openglWindow = new OpenGLWindow();
        m_openglWindow->Init("OpenGL");
        
        while(m_isActive)
        {
            windowActive->ProcessHandler();
            m_isActive = m_openglWindow->ProcessHandler();
        }
	}


	Stage::~Stage()
	{
		delete windowActive;
        delete m_openglWindow;
	}

	WindowActiveMgr* Stage::windowActive = nullptr;
}
