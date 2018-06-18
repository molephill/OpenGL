
#ifndef BASEWINDOW_HPP
#define BASEWINDOW_HPP

#include <iostream>

#include "Define.h"
#include "WindowActiveMgr.hpp"

namespace Liar
{
	class BaseWindow
	{
	public:
		BaseWindow();
        BaseWindow(std::string, unsigned int w = WINDOW_W, unsigned int h = WINDOW_H);
		virtual ~BaseWindow();

	protected:
		GLFWwindow* m_window;
        bool m_isFirstMouse;
        double m_lastMouseX;
        double m_lastMouseY;

	public:
		GLFWwindow* GetWindow() { return m_window; };

	protected:
		virtual bool Created();
		virtual void Render();

	public:
		bool Init(std::string, unsigned int w = WINDOW_W, unsigned int h = WINDOW_H);
        bool ProcessHandler();

	public:
		virtual void KeyInputEvent();
        virtual void SetSize(unsigned int, unsigned int);
		virtual bool MouseEvent(double, double);
		virtual void ScrollEvent(double, double);
	};
}

#endif	/* BASEWINDOW_HPP */
