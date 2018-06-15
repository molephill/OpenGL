
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
		virtual ~BaseWindow();

	protected:
		GLFWwindow* m_window;

	public:
		GLFWwindow* GetWindow() { return m_window; };

	protected:
		virtual bool Created();
		virtual void Render();

	public:
		bool Init(std::string, unsigned int w = WINDOW_W, unsigned int h = WINDOW_H);
		virtual void SetSize(unsigned int, unsigned int);
        bool ProcessHandler();

	public:
		virtual void KeyInputEvent();
		virtual void MouseEvent(double, double);
		virtual void ScrollEvent(double, double);
	};
}

#endif	/* BASEWINDOW_HPP */
