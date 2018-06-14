
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
		BaseWindow(WindowActiveMgr* handler = nullptr);
		virtual ~BaseWindow();

	protected:
		GLFWwindow* m_window;
		WindowActiveMgr* m_handler;

	public:
		GLFWwindow* GetWindow() { return m_window; };

	protected:
		virtual bool Created();
		virtual void Render();
		virtual void Destory();

	public:
		bool Init(std::string, unsigned int w = WINDOW_W, unsigned int h = WINDOW_H);
		virtual void SetSize(unsigned int, unsigned int);
	};
}

#endif	/* BASEWINDOW_HPP */