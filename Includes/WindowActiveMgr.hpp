
#ifndef BASEWINDOWACTIVEMGR_HPP
#define BASEWINDOWACTIVEMGR_HPP

//#include "BaseWindow.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

namespace Liar
{
	class BaseWindow;

	class WindowActiveMgr
	{
	public:
		WindowActiveMgr();
		~WindowActiveMgr();

	private:
		BaseWindow* m_handler;

	public:
		void RegisttHandler(BaseWindow* handler = nullptr);
		void SetSize(unsigned int, unsigned int);
	};
}

#endif	/* BASEWINDOWACTIVEMGR_HPP */