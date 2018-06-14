
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "ViewPort.h"
#include "Component.hpp"

namespace Liar
{
	class Camera
	{
	public:
		Camera();
		Camera(glm::vec3, glm::vec3);
		Camera(glm::vec3, glm::vec3, float yaw = CAMERA_YAW, float pitch = CAMERA_PITCH);
		Camera(float, float, float, float ux = 0.0f, float uy = 1.0f, float uz = 0.0f);
		Camera(float, float, float, float, float, float, float yaw = CAMERA_YAW, float pitch = CAMERA_PITCH);
		~Camera();

	private:
		CPosition* m_position;
		CRotation* m_rotation;

		ViewPort* m_viewPort;

		glm::vec3 m_front;
		glm::vec3 m_worldUp;

		// 矩阵
		glm::mat4 m_mixMatrix;

		// 是否是脏数据
		bool m_isDirty;

	public:
		// ===================================================
		void SetPosition(const glm::vec3&);
		void SetPosition(float, float, float);
		// ===================================================
		void SetRotation(const glm::vec3&);
		void SetRotation(float, float, float);
		// ===================================================
		void SetFront(const glm::vec3&);
		void SetFront(float, float, float);
		// ===================================================
		void SetWorldUp(const glm::vec3&);
		void SetWorldUp(float, float, float);
		// ===================================================
		void SetSize(unsigned int, unsigned int);
		void SetViewParams(float n, float f, float fov = CAMERA_FOV, CAMERA_TYPE type = CAMERA_TYPE::PERPECTIVE);

	public:
		// ===================================================
		BaseComponent* GetPosition() { return m_position; };
		BaseComponent* GetRotation() { return m_rotation; };

		float GetX() { return m_position->GetX(); };
		float GetY() { return m_position->GetY(); };
		float GetZ() { return m_position->GetZ(); };

		float GetRX() { return m_rotation->GetX(); };
		float GetRY() { return m_rotation->GetY(); };
		float GetRZ() { return m_rotation->GetZ(); };
		// ===================================================
		// ===================================================
		// ===================================================
		ViewPort* GetViewPort() { return m_viewPort; };
		glm::mat4& GetMatrix() { return m_mixMatrix; };

		void Render();
	};
}

#endif /* CAMERA_HPP */
