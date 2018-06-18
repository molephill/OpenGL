#include "BaseWindow.hpp"

namespace Liar
{
    BaseWindow::BaseWindow():m_isFirstMouse(true),m_lastMouseX(0.0),m_lastMouseY(0.0)
	{
	}
    
    BaseWindow::BaseWindow(std::string title, unsigned int w, unsigned int h)
    {
        this->Init(title, w, h);
    }

	BaseWindow::~BaseWindow()
	{
        glfwTerminate();
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

		// create success
		if (!this->Created())
		{
			return false;
		}

		return true;
	}

	// created_call_back
	bool BaseWindow::Created()
	{
		return true;
	}

	// render_handler
	void BaseWindow::Render()
	{
        
	}
    
    bool BaseWindow::ProcessHandler()
    {
        if(!glfwWindowShouldClose(m_window))
        {
            Render();
            
            glfwSwapBuffers(m_window);
            glfwPollEvents();
            return true;
        }
        else{
            return false;
        }
    }
    
    // Ðresize
    void BaseWindow::SetSize(unsigned int, unsigned int)
    {
        
    }

	// keyInput
	void BaseWindow::KeyInputEvent()
	{
        if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_window, true);
        }
	}

	// mouse
	bool BaseWindow::MouseEvent(double x, double y)
	{
        int sx = 0, sy = 0;
        int w = 0, h = 0;
        
        glfwGetWindowPos(m_window, &sx, &sy);
        glfwGetWindowSize(m_window, &w, &h);
        
        int ex = sx + w;
        int ey = sy + h;
        
        return x >= sx && x <= ex && y >= sy && y <= ey;
	}

	// scroll
	void BaseWindow::ScrollEvent(double, double)
	{

	}
    
}
