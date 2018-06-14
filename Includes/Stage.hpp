
#ifndef Stage_hpp
#define Stage_hpp

#include "WindowActiveMgr.hpp"
#include "OpenGLWindow.hpp"

namespace Liar
{
	class Stage
	{
	public:
		Stage();
		~Stage();

	private:
        bool m_isActive;
		OpenGLWindow* m_openglWindow;

	public:
		static WindowActiveMgr* windowActive;
	};
}

#endif /* Stage_hpp */
