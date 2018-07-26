
#ifndef Stage_hpp
#define Stage_hpp

#include "WindowActiveMgr.hpp"
#include "OpenGLWindow.hpp"
#include "RenderMgr.hpp"

namespace Liar
{
	class Stage
	{
	public:
		Stage();
		~Stage();

	private:
        bool m_isActive;
		OpenGLWindow* m_openglMainWindow;
        WindowActiveMgr* m_windowActive;
		RenderMgr* m_renderMgr;
	};
}

#endif /* Stage_hpp */
