
#ifndef VIEWPORT_HPP
#define VIEWPORT_HPP

#include "Define.h"

#include <gtc/matrix_transform.hpp>

namespace Liar
{
	class ViewPort
	{
	public:
		ViewPort();
		ViewPort(unsigned int, unsigned int);
		ViewPort(unsigned int, unsigned int, float, float, float);
		~ViewPort();

	private:
		unsigned int m_width;
		unsigned int m_height;

		float m_backRed;
		float m_backGreen;
		float m_backBlue;
		float m_backAlpha;

		//
		bool m_isDirty;

		// 其他参数
		CAMERA_TYPE m_cameraType;
		glm::vec3 m_cameraParams;
		glm::mat4 m_matrix;

	public:
		bool SetSize(const glm::uvec2&);
		bool SetSize(unsigned int, unsigned int);
		// ==================================================
        bool ChangeFov(float);
        bool ChangeType(CAMERA_TYPE);
        // ==================================================
		void SetBackground(const glm::vec4&);
		void SetBackground(const glm::vec3&, float a = 1.0);
		void SetBackground(float, float, float, float a = 1.0);
		// ===================================================
		bool SetViewParams(float, float, float fov = CAMERA_FOV, CAMERA_TYPE type = CAMERA_TYPE::PERPECTIVE);
		// ==================================================
		glm::mat4& GetViewMatrix();
		// ==================================================
		float GetAspect() { return static_cast<float>(m_width / m_height); };
		unsigned int GetWidth() { return m_width; };
		unsigned int GetHeight() { return m_height; };
        float GetFov() { return m_cameraParams.z; };
		void Render();
	};
}

#endif /* VIEWPORT_HPP */
