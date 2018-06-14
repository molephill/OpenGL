#include "BaseWindow.hpp"

namespace Liar
{
	BaseWindow::BaseWindow()
	{
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
		if (!Created())
		{
			return false;
		}

		return true;
	}

	// Ðresize
	void BaseWindow::SetSize(unsigned int, unsigned int)
	{

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
    
}
