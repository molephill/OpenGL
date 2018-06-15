#include "WindowActiveMgr.hpp"
#include "BaseWindow.hpp"
#include "Stage.hpp"

namespace Liar
{
	WindowActiveMgr::WindowActiveMgr()
	{
	}


	WindowActiveMgr::~WindowActiveMgr()
	{
	}

	void WindowActiveMgr::RegisttHandler(BaseWindow* handler)
	{
		m_handler = handler;

		GLFWwindow* window = m_handler ? m_handler->GetWindow() : nullptr;
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}

	void WindowActiveMgr::SetSize(unsigned int w, unsigned int h)
	{
		if (m_handler)
		{
			m_handler->SetSize(w, h);
		}
	}
}

// ��Ӧ�����¼�
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else
	{

	}
}

// �޸���Ļ��Сʱ
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//glViewport(0, 0, width, height);
	Liar::Stage::windowActive->SetSize(width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}