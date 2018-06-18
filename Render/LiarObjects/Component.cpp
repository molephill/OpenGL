#include "Component.hpp"

namespace Liar
{
	bool BaseComponent::SetValue(const glm::vec3& val)
	{
		if (m_val != val)
		{
			m_val = val;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool BaseComponent::SetValue(float x, float y, float z)
	{
		if (m_val.x != x || m_val.y != y || m_val.z != z)
		{
			m_val.x = x;
			m_val.y = y;
			m_val.z = z;
			return true;
		}
		else
		{
			return false;
		}
	}
    
    bool BaseComponent::AddValue(const glm::vec3& val)
    {
        if(val.x != 0 || val.y != 0 || val.z != 0)
        {
            m_val += val;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool BaseComponent::AddValue(float x, float y, float z)
    {
        if(x != 0 || y != 0 || z != 0)
        {
            m_val.x += x;
            m_val.y += y;
            m_val.z += z;
            return true;
        }
        else
        {
            return false;
        }
    }

	void BaseComponent::GetValue(glm::vec3& out)
	{
		out.x = m_val.x;
		out.y = m_val.y;
		out.z = m_val.z;
	}

	glm::vec3& BaseComponent::GetValue()
	{
		return m_val;
	}
}
