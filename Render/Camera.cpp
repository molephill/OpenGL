#include "Camera.hpp"

namespace Liar
{
	Camera::Camera():
		m_position(new CPosition(0.0f, 0.0f, 0.0f))
		, m_rotation(new CRotation(CAMERA_YAW, CAMERA_PITCH, 0))
		, m_viewPort(new ViewPort())
		, m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
		, m_front(glm::vec3(0.0f, 0.0f, -1.0f))
		, m_mixMatrix(glm::mat4(1.0))
		, m_isDirty(true)
	{
	}

	Camera::Camera(glm::vec3 pos, glm::vec3 up): 
		m_position(new CPosition(pos))
		, m_rotation(new CRotation(CAMERA_YAW, CAMERA_PITCH, 0))
		, m_viewPort(new ViewPort())
		, m_worldUp(up)
		, m_mixMatrix(glm::mat4(1.0))
		, m_isDirty(true)
	{
	}

	Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch) : 
		m_position(new CPosition(pos))
		, m_rotation(new CRotation(yaw, pitch, 0))
		, m_viewPort(new ViewPort())
		, m_worldUp(up)
		, m_mixMatrix(glm::mat4(1.0))
		, m_isDirty(true)
	{
	}

	Camera::Camera(float px, float py, float pz, float ux, float uy, float uz) : 
		m_position(new CPosition(px, py, pz))
		, m_rotation(new CRotation(CAMERA_YAW, CAMERA_PITCH, 0))
		, m_viewPort(new ViewPort())
		, m_worldUp(glm::vec3(ux, uy, ux))
		, m_mixMatrix(glm::mat4(1.0))
		, m_isDirty(true)
	{
	}

	Camera::Camera(float px, float py, float pz, float ux, float uy, float uz, float yaw, float pitch) : 
		m_position(new CPosition(px, py, pz))
		, m_rotation(new CRotation(yaw, pitch, 0))
		, m_viewPort(new ViewPort())
		, m_worldUp(glm::vec3(ux, uy, ux))
		, m_mixMatrix(glm::mat4(1.0))
		, m_isDirty(true)
	{
	}

	Camera::~Camera()
	{
		delete m_viewPort;
	}

	// ===================================================
	void Camera::SetPosition(const glm::vec3& pos)
	{
		if (m_position->SetValue(pos))
		{
			m_isDirty = true;
		}
	}

	void Camera::SetPosition(float x, float y, float z)
	{
		if (m_position->SetValue(x, y, z))
		{
			m_isDirty = true;
		}
	}

	// ===================================================
	void Camera::SetWorldUp(const glm::vec3& up)
	{
		if (m_worldUp != up)
		{
			m_worldUp = up;

			m_isDirty = true;
		}
	}

	void Camera::SetWorldUp(float x, float y, float z)
	{
		if (m_worldUp.x != x || m_worldUp.y != y || m_worldUp.z != z)
		{
			m_worldUp.x = x;
			m_worldUp.y = y;
			m_worldUp.z = z;
			m_isDirty = true;
		}
	}

	// ===================================================
	void Camera::SetFront(const glm::vec3& front)
	{
		if (m_front != front)
		{
			m_front = front;
			m_isDirty = true;
		}
	}

	void Camera::SetFront(float x, float y, float z)
	{
		if (m_front.x != x || m_front.y != y || m_front.z != z)
		{
			m_front.x = x;
			m_front.y = y;
			m_front.z = z;
			m_isDirty = true;
		}
	}

	// ===================================================
	void Camera::SetRotation(const glm::vec3& r)
	{
		if (m_rotation->SetValue(r))
		{
			m_isDirty = true;
		}
	}

	void Camera::SetRotation(float x, float y, float z)
	{
		if (m_rotation->SetValue(x, y, z))
		{
			m_isDirty = true;
		}
	}

	// ==================================================
	void Camera::SetViewParams(float n, float f, float fov, CAMERA_TYPE type)
	{
		if (m_viewPort->SetViewParams(n, f, fov, type))
		{
			m_isDirty = true;
		}
	}

	void Camera::SetSize(unsigned int w, unsigned int h)
	{
		if (m_viewPort->SetSize(w, h))
		{
			m_isDirty = true;
		}
	}

	// ==================================================
	void Camera::Render()
	{
		m_viewPort->Render();

		if (m_isDirty)
		{
			// ========================== prespectiveMatrix ===============
			glm::mat4 projection = m_viewPort->GetPerspective();

			// =============================== viewMatrix =================
			float yaw = m_rotation->GetX();
			float pitch = m_rotation->GetY();

			m_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			m_front.y = sin(glm::radians(pitch));
			m_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			m_front = glm::normalize(m_front);

			glm::vec3 right = glm::normalize(glm::cross(m_front, m_worldUp));
			glm::vec3 up = glm::normalize(glm::cross(right, m_front));

			glm::vec3 pos = m_position->GetValue();
			glm::mat4 viewMatrix = glm::lookAt(pos, pos + m_front, up);

			// =============================== viewMatrix =================

			m_mixMatrix = projection * viewMatrix;

			m_isDirty = false;
		}
	}

}
