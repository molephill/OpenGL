#include <LiarPluginRead.h>

#include "AssetsMgr.hpp"

#include "Entity.h"
#include "Model.h"

namespace Liar
{
	Entity::Entity()
		:m_x(0.0f),m_y(0.0f),m_z(0.0f)
		, m_rotationX(0.0f), m_rotationY(0.0f), m_rotationZ(0.0f)
		, m_scaleX(1.0f), m_scaleY(1.0f), m_scaleZ(1.0f)
		, m_transformChanged(true), m_name("")
		, m_parent(nullptr), m_childrenNode(nullptr), m_nextChildNode(nullptr)
		, m_transform(new Liar::Matrix4())
	{
	}


	Entity::~Entity()
	{
	}

	// =============== change posistion ==================

	void Entity::SetX(float v)
	{
		if (m_x != v)
		{
			m_x = v;
			m_transformChanged = true;
		}
	}

	void Entity::SetY(float v)
	{
		if (m_y != v)
		{
			m_y = v;
			m_transformChanged = true;
		}
	}

	void Entity::SetZ(float v)
	{
		if (m_z != v)
		{
			m_z = v;
			m_transformChanged = true;
		}
	}

	void Entity::SetPosition(float x, float y, float z)
	{
		if (m_x != x || m_y != y || m_z != z)
		{
			m_x = x;
			m_y = y;
			m_z = z;
			m_transformChanged = true;
		}
	}

	void Entity::SetPosition(const Liar::Vector3D& v)
	{
        SetPosition(v.x, v.y, v.z);
	}

	// ================ change rotation ==================== 
	void Entity::SetRotationX(float v)
	{
		if (m_rotationX != v)
		{
			m_rotationX = v;
			m_transformChanged = true;
		}
	}

	void Entity::SetRotationY(float v)
	{
		if (m_rotationY != v)
		{
			m_rotationY = v;
			m_transformChanged = true;
		}
	}

	void Entity::SetRotationZ(float v)
	{
		if (m_rotationZ != v)
		{
			m_rotationZ = v;
			m_transformChanged = true;
		}
	}
    
    void Entity::SetRotation(float r)
    {
        SetRotation(r, r, r);
    }

	void Entity::SetRotation(float x, float y, float z)
	{
		if (m_rotationX != x || m_rotationY != y || m_rotationZ != z)
		{
			m_rotationX = x;
			m_rotationY = y;
			m_rotationZ = z;
			m_transformChanged = true;
		}
	}

	void Entity::SetRotation(const Liar::Vector3D& v)
	{
        SetRotation(v.x, v.y, v.z);
	}

	// ======================== change Scale ==========================
	void Entity::SetScaleX(float v)
	{
		if (m_scaleX != v)
		{
			m_scaleX = v;
			m_transformChanged = true;
		}
	}

	void Entity::SetScaleY(float v)
	{
		if (m_scaleY != v)
		{
			m_scaleY = v;
			m_transformChanged = true;
		}
	}

	void Entity::SetScaleZ(float v)
	{
		if (m_scaleZ != v)
		{
			m_scaleZ = v;
			m_transformChanged = true;
		}
	}
    
    void Entity::SetScale(float scale)
    {
        SetScale(scale, scale, scale);
    }

	void Entity::SetScale(float x, float y, float z)
	{
		if (m_scaleX != x || m_scaleY != y || m_scaleZ != z)
		{
			m_scaleX = x;
			m_scaleY = y;
			m_scaleZ = z;
			m_transformChanged = true;
		}
	}

	void Entity::SetScale(const Liar::Vector3D& v)
	{
        SetScale(v.x, v.y, v.z);
	}
    
    void Entity::AddX(float x)
    {
        if(x != 0)
        {
            m_x += x;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddY(float y)
    {
        if(y != 0)
        {
            m_y += y;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddZ(float z)
    {
        if(z != 0)
        {
            m_z += z;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddPosition(float x, float y, float z)
    {
        if(x != 0 || y != 0 || z != 0)
        {
            m_x += x;
            m_y += y;
            m_z += z;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddPosition(const Liar::Vector3D& v)
    {
        AddPosition(v.x, v.y, v.z);
    }
    
    void Entity::AddScaleX(float x)
    {
        if(x != 0)
        {
            m_scaleX += x;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddScaleY(float y)
    {
        if(y != 0)
        {
            m_scaleY += y;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddScaleZ(float z)
    {
        if(z != 0)
        {
            m_scaleZ += z;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddScale(float x, float y, float z)
    {
        if(x != 0 || y != 0 || z != 0)
        {
            m_scaleX += x;
            m_scaleY += y;
            m_scaleZ += z;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddScale(const Liar::Vector3D& v)
    {
        AddScale(v.x, v.y, v.z);
    }
    
    void Entity::AddRotationX(float x)
    {
        if(x != 0)
        {
            m_rotationX += x;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddRotationY(float y)
    {
        if(y != 0)
        {
            m_rotationY += y;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddRotationZ(float z)
    {
        if(z != 0)
        {
            m_rotationZ += z;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddRotation(float x, float y, float z)
    {
        if(x != 0 || y != 0 || z != 0)
        {
            m_rotationX += x;
            m_rotationY += y;
            m_rotationZ += z;
            m_transformChanged = true;
        }
    }
    
    void Entity::AddRotation(const Liar::Vector3D& v)
    {
        AddRotation(v.x, v.y, v.z);
    }
    
    // ================= Child =================
    Liar::Entity* Entity::AddChild(Liar::Entity * child)
    {
        if(!child)
        {
            std::cout << "Add nullptr ERROR!!" << std::endl;
            return nullptr;
        }
		if (child->m_parent == this) return child;
		if (child->m_parent) child->m_parent->RemoveChild(child);
        child->m_parent = this;
        if(!m_childrenNode)
        {
            m_childrenNode = child;
        }
        else
        {
			Liar::Entity* current = m_childrenNode;
			while (current)
			{
				if (!current->m_nextChildNode)
				{
					current->m_nextChildNode = child;
					break;
				}
				current = current->m_nextChildNode;
			}
        }
 
        return child;
    }
    
    Liar::Entity* Entity::AddModel(const std::string& path)
    {
        Liar::Model* model = Liar::LiarPluginRead::ReadModel(AssetsMgr::GetPath(path.c_str()));
        return AddChild(model);
    }
    
    Liar::Entity* Entity::RemoveChild(Liar::Entity* child)
    {
        bool find = false;
        if(m_childrenNode)
        {
			Liar::Entity* pre = nullptr;
			Liar::Entity* current = m_childrenNode;
			while (current)
			{
				if (current == child)
				{
					if (pre)
					{
						pre->m_nextChildNode = current->m_nextChildNode;
					}
					else
					{
						m_childrenNode = current->m_nextChildNode;
					}
					find = true;
					break;
				}
				current->m_nextChildNode = nullptr;
				pre = current;
				current = current->m_nextChildNode;
			}
        }
        
        if(find)
        {
            child->m_parent = nullptr;
            return child;
        }
        else
        {
            return nullptr;
        }
    }
    
    Liar::Entity* Entity::RemoveChild(const std::string& name)
    {
        Liar::Entity* findNode = nullptr;
        if(m_childrenNode)
        {
			Liar::Entity* pre = nullptr;
			Liar::Entity* current = m_childrenNode;
			while (current)
			{
				if (current->m_name == name)
				{
					if (pre)
					{
						pre->m_nextChildNode = current->m_nextChildNode;
					}
					else
					{
						m_childrenNode = current->m_nextChildNode;
					}
					findNode = current;
					break;
				}
				current->m_nextChildNode = nullptr;
				pre = current;
				current = current->m_nextChildNode;
			}
        }
        
        if(findNode)
        {
            findNode->m_parent = nullptr;
        }
        return findNode;
    }
    
    bool Entity::RemoveAndDisposeChild(Liar::Entity* child)
    {
        Liar::Entity* findChild = RemoveChild(child);
        if(findChild == child)
        {
            delete child;
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool Entity::RemoveAndDisposeChild(const std::string& name)
    {
        Liar::Entity* findChild = RemoveChild(name);
        if(findChild)
        {
            delete findChild;
            return true;
        }
        else
        {
            return false;
        }
    }

	// ================== render ==================
	void Entity::CalcTransform(bool calcInvert)
	{
		if (m_transformChanged)
		{
			m_transform->Identity();
			m_transform->Scale(m_scaleX, m_scaleY, m_scaleZ);
			m_transform->Rotate(m_rotationX, 1, 0, 0);
			m_transform->Rotate(m_rotationY, 0, 1, 0);
			m_transform->Rotate(m_rotationZ, 0, 0, 1);
			m_transform->Translate(m_x, m_y, m_z);
			m_transformChanged = false;
		}
	}
    
    void Entity::Render(Liar::Shader& shader)
    {
        bool parentChanged = m_transformChanged;
        CalcTransform();
        shader.SetMat4("model", *m_transform);
        RenderChildren(shader, parentChanged);
    }
    
    void Entity::RenderChildren(Liar::Shader& shader, bool parentChanged)
    {
        Liar::Entity* child = m_childrenNode;
        while (child)
        {
            /*char tx[100];
            sprintf(tx, "%f %f %f %f %f %f %f %f", m_x, m_y, m_z, m_scaleX, m_scaleY, m_scaleZ, m_rotationX, m_rotationY, m_rotationZ);
            std::cout << child->m_name << "===" << parentChanged << "==" << tx << std::endl;*/
            if(parentChanged)
            {
				child->AddScale(m_scaleX, m_scaleY, m_scaleZ);
				child->AddRotation(m_rotationX, m_rotationY, m_rotationZ);
				child->AddPosition(m_x, m_y, m_z);
            }
            child->Render(shader);
            child = child->m_nextChildNode;
        }
    }

	std::ostream& operator<<(std::ostream& os, const Liar::Entity& m)
	{
		os << "position(x:" << m.m_x << "," << m.m_y << "," << m.m_z << "),\n";
		os << "rotation(x:" << m.m_rotationX << "," << m.m_rotationX << "," << m.m_rotationZ << "),\n";
		os << "scale(x:" << m.m_scaleX << "," << m.m_scaleY << "," << m.m_scaleZ << "),\n";
		return os;
	}

	///////////////////////////////////////////////////////////////////////////////
	// draw the local axis of an object
	///////////////////////////////////////////////////////////////////////////////
	void Entity::DrawAxis(float size)
	{
		
	}

}
