#include "ViewPort.h"

namespace Liar
{
	ViewPort::ViewPort():
		m_width(WINDOW_W), m_height(WINDOW_H)
		, m_backRed(0.0f), m_backGreen(0.0f), m_backBlue(0.0f)
		, m_backAlpha(1.0f)
		, m_cameraType(CAMERA_TYPE::PERPECTIVE)
		, m_cameraParams(glm::vec3(0.1, 100.0f, CAMERA_FOV))
	{
	}

	ViewPort::ViewPort(unsigned int w, unsigned int h) :
		m_width(w), m_height(h)
		, m_backRed(0.0f), m_backGreen(0.0f), m_backBlue(0.0f)
		, m_backAlpha(1.0f)
		, m_cameraType(CAMERA_TYPE::PERPECTIVE)
		, m_cameraParams(glm::vec3(0.1, 100.0f, CAMERA_FOV))
	{
	}

	ViewPort::ViewPort(unsigned int w, unsigned int h, float r, float g, float b) :
		m_width(w), m_height(h)
		, m_backRed(r), m_backGreen(g), m_backBlue(b)
		, m_backAlpha(1.0f)
		, m_cameraType(CAMERA_TYPE::PERPECTIVE)
		, m_cameraParams(glm::vec3(0.1, 100.0f, CAMERA_FOV))
	{
	}


	ViewPort::~ViewPort()
	{
	}

	// ==================================================
	bool ViewPort::SetSize(const glm::uvec2& val)
	{
		if (val.x != m_width || val.y != m_height)
		{
			m_width = val.x;
			m_height = val.y;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool ViewPort::SetSize(unsigned int w, unsigned int h)
	{
		if (w != m_width || h != m_height)
		{
			m_width = w;
			m_height = h;
			return true;
		}
		else
		{
			return false;
		}
	}

	// ==================================================
	void ViewPort::SetBackground(const glm::vec4& val)
	{
		m_backRed = val.x;
		m_backGreen = val.y;
		m_backBlue = val.z;
		m_backAlpha = val.w;
	}

	void ViewPort::SetBackground(const glm::vec3& val, float a)
	{
		m_backRed = val.x;
		m_backGreen = val.y;
		m_backBlue = val.z;
		m_backAlpha = a;
	}

	void ViewPort::SetBackground(float r, float g, float b, float a)
	{
		m_backRed = r;
		m_backGreen = g;
		m_backBlue = b;
		m_backAlpha = a;
	}

	bool ViewPort::SetViewParams(float n, float f, float fov, CAMERA_TYPE type)
	{
		if (m_cameraType != type || m_cameraParams.x != n || m_cameraParams.y != f || m_cameraParams.z != fov)
		{
			m_cameraType = type;
			m_cameraParams.x = n;
			m_cameraParams.y = f;
			m_cameraParams.z = fov;
			return true;
		}
		else
		{
			return false;
		}
	}
    
    bool ViewPort::ChangeFov(float fov)
    {
        if(m_cameraParams.z != fov)
        {
            m_cameraParams.z = fov;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool ViewPort::ChangeType(CAMERA_TYPE type)
    {
        if(m_cameraType != type)
        {
            m_cameraType = type;
            return true;
        }
        else
        {
            return false;
        }
    }

	glm::mat4 ViewPort::GetPerspective()
	{
		return m_cameraType == CAMERA_TYPE::PERPECTIVE ?
			glm::perspective(glm::radians(m_cameraParams.z), GetAspect(), m_cameraParams.x, m_cameraParams.y)
			: glm::ortho(0.0f, static_cast<float>(m_width), 0.0f, static_cast<float>(m_height), m_cameraParams.x, m_cameraParams.y);
	}

	// ==================================================
	void ViewPort::Render()
	{
		glClearColor(m_backRed, m_backGreen, m_backBlue, m_backAlpha);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
