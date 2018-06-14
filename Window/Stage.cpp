#include "Stage.hpp"

namespace Liar
{
	Stage::Stage()
	{
		windowActive = new WindowActiveMgr();

		m_openglWindow = new OpenGLWindow(windowActive);
		m_openglWindow->Init("OpenGL");
	}


	Stage::~Stage()
	{
		delete windowActive;
	}

	WindowActiveMgr* Stage::windowActive = nullptr;
}
