#include "WindowActiveMgr.hpp"
#include "BaseWindow.hpp"
#include "Global.hpp"

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
    
    void WindowActiveMgr::ProcessHandler()
    {
        if(m_handler)
        {
            m_handler->KeyInputEvent();
        }
    }
}

// 修改屏幕大小时
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if(Liar::Global::windowActive->GetHandler())
    {
        Liar::Global::windowActive->GetHandler()->SetSize(width, height);
    }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(Liar::Global::windowActive->GetHandler())
    {
        Liar::Global::windowActive->GetHandler()->MouseEvent(xpos, ypos);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(Liar::Global::windowActive->GetHandler())
    {
        Liar::Global::windowActive->GetHandler()->ScrollEvent(xoffset, yoffset);
    }
}
