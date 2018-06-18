//
//  OpenGLWindow.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/19.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef OpenGLWindow_hpp
#define OpenGLWindow_hpp

#include "BaseWindow.hpp"
#include "RenderMgr.hpp"

using namespace std;

namespace Liar
{
    class OpenGLWindow
		:public BaseWindow
    {
	public:
		OpenGLWindow();
        OpenGLWindow(string title, unsigned int w = WINDOW_W, unsigned int h = WINDOW_H);

	protected:
		virtual bool Created();
		virtual void Render();

	public:
		virtual void KeyInputEvent();
        virtual void SetSize(unsigned int, unsigned int);
        virtual bool MouseEvent(double, double);
        virtual void ScrollEvent(double, double);
        
    private:
        RenderMgr* m_renderMgr;
    };
}

#endif /* OpenGLWindow_hpp */
