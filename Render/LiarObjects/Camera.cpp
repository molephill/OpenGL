#include "Camera.hpp"
#include "LiarUtil.hpp"

namespace Liar
{
	Camera::Camera():Liar::LiarObject()
		, m_viewPort(new ViewPort())
		, m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
		, m_front(glm::vec3(0.0f, 0.0f, -1.0f))
		, m_mixMatrix(glm::mat4(1.0))
        , m_constrainPitch(true)
	{
        SetRotation(CAMERA_PITCH, CAMERA_YAW, 0.0f);
	}
    
    Camera::Camera(float x, float y, float z):Liar::LiarObject(x, y, z)
        , m_viewPort(new ViewPort())
        , m_worldUp(glm::vec3(0.0f, 1.0f, 0.0f))
        , m_front(glm::vec3(0.0f, 0.0f, -1.0f))
        , m_mixMatrix(glm::mat4(1.0))
        , m_constrainPitch(true)
    {
        SetRotation(CAMERA_PITCH, CAMERA_YAW, 0.0f);
    }

	Camera::~Camera()
	{
		delete m_viewPort;
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
    void Camera::SetRotation(const glm::vec3& r)
    {
        float x = GetRX();
        if(m_constrainPitch)
        {
            x = x > 89.0f ? 89.0f : x;
            x = x < -89.0f ? - 89.0f : x;
            m_rotation->SetValue(x, GetRY(), GetRZ());
        }
        if (m_rotation->SetValue(x, r.y, r.z))
        {
            m_isDirty = true;
        }
    }
    
    void Camera::SetRotation(float x, float y, float z)
    {
        x = x > 89.0f ? 89.0f : x;
        x = x < -89.0f ? - 89.0f : x;
        if (m_rotation->SetValue(x, y, z))
        {
            m_isDirty = true;
        }
    }
    
    // ===================================================
    void Camera::AddRotation(const glm::vec3& r)
    {
        if (m_rotation->AddValue(r))
        {
            m_isDirty = true;
        }
    }
    
    void Camera::AddRotation(float x, float y, float z)
    {
        if (m_rotation->AddValue(x, y, z))
        {
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
    
    void Camera::SetFov(float fov)
    {
        if(m_viewPort->ChangeFov(fov))
        {
            m_isDirty = true;
        }
    }
    
    void Camera::AddFov(float fov)
    {
        float oldFov = m_viewPort->GetFov();
        if(oldFov >= 1.0f && oldFov <= 45.0f)
        {
            float newFov = oldFov + fov;
            SetFov(newFov);
        }
        else if(oldFov < 1.0)
        {
            SetFov(1.0);
        }
        else
        {
            SetFov(45.0f);
        }
    }
    
    void Camera::SetType(CAMERA_TYPE type)
    {
        if(m_viewPort->ChangeType(type))
        {
            m_isDirty = true;
        }
    }
    
    // ==================================================
    void Camera::MoveForward(MOVE_DIRECTION type)
    {
        float velocity = Global::cameraMoveSpeed * Global::delataTime;
        
        switch(type)
        {
            case MOVE_DIRECTION::FORWARD:
                AddPosition(m_front*velocity);
                break;
            case MOVE_DIRECTION::BACKWARD:
                AddPosition(-m_front*velocity);
                break;
            case MOVE_DIRECTION::RIGHT:
                AddPosition(m_right*velocity);
                break;
            case MOVE_DIRECTION::LEFT:
                AddPosition(-m_right*velocity);
                break;
            default:
                break;
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
			float pitch = m_rotation->GetX();
			float yaw = m_rotation->GetY();

			m_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			m_front.y = sin(glm::radians(pitch));
			m_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			m_front = glm::normalize(m_front);

			m_right = glm::normalize(glm::cross(m_front, m_worldUp));
			glm::vec3 up = glm::normalize(glm::cross(m_right, m_front));

			glm::vec3 pos = m_position->GetValue();
//            glm::mat4 viewMatrix = glm::lookAt(pos, pos + m_front, up);
            glm::mat4 viewMatrix = LiarUtil::LookAt(pos, pos + m_front, up);

			// =============================== viewMatrix =================

			m_mixMatrix = projection * viewMatrix;

			m_isDirty = false;
		}
	}

}
