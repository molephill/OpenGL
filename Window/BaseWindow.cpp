#include "BaseWindow.hpp"

namespace Liar
{
	BaseWindow::BaseWindow(WindowActiveMgr* handler):
		m_handler(handler),m_window(nullptr)
	{
		
	}

	BaseWindow::~BaseWindow()
	{
	}

	bool BaseWindow::Init(std::string title, unsigned int w, unsigned int h)
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

		m_window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);

		if (!m_window) {
			glfwTerminate();
			return false;
		}

		// 创建成功回调
		if (!Created())
		{
			return false;
		}

		while (!glfwWindowShouldClose(m_window)) {

			// -- input --
			if (m_handler)
			{
				m_handler->ProcessHandler();
			}

			// -- render --
			Render();

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}

		Destory();

		glfwTerminate();

		return true;
	}

	// 修改大小
	void BaseWindow::SetSize(unsigned int, unsigned int)
	{

	}

	// 创建成功时的回调
	bool BaseWindow::Created()
	{
		return true;
	}

	// 刷新时
	void BaseWindow::Render()
	{

	}

	void BaseWindow::Destory()
	{

	}

}
