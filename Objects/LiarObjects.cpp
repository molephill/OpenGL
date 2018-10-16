#include <LiarPluginRead.h>

#include "AssetsMgr.hpp"
#include "LiarModel.h"

namespace Liar
{
    LiarDisplayObject::LiarDisplayObject()
        : m_position(new Liar::Vector3D()),
        m_rotation(new Liar::Vector3D()),
        m_scale(new Liar::Vector3D(1.0f, 1.0f, 1.0f)),
        m_transformChanged(true), m_name(""),
        m_parent(nullptr),
        m_childrenNode(nullptr), m_nextChildNode(nullptr),
        m_transform(new Liar::Matrix4())
    {
        
    }
    
    LiarDisplayObject::~LiarDisplayObject()
    {
        delete m_position;
        delete m_rotation;
        delete m_scale;
        delete m_transform;
    }
    
    // =============== change posistion ==================
    
    void LiarDisplayObject::SetX(float v)
    {
        if (m_position->x != v)
        {
            m_position->x = v;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetY(float v)
    {
        if (m_position->y != v)
        {
            m_position->y = v;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetZ(float v)
    {
        if (m_position->z != v)
        {
            m_position->z = v;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetPosition(float x, float y, float z)
    {
        if (m_position->x != x || m_position->y != y || m_position->z != z)
        {
            m_position->Set(x, y, z);
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetPosition(const Liar::Vector3D& v)
    {
        SetPosition(v.x, v.y, v.z);
    }
    
    // ================ change rotation ====================
    void LiarDisplayObject::SetRotationX(float v)
    {
        if (m_rotation->x != v)
        {
            m_rotation->x = v;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetRotationY(float v)
    {
        if (m_rotation->y != v)
        {
            m_rotation->y = v;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetRotationZ(float v)
    {
        if (m_rotation->z != v)
        {
            m_rotation->z = v;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetRotation(float r)
    {
        SetRotation(r, r, r);
    }
    
    void LiarDisplayObject::SetRotation(float x, float y, float z)
    {
        if (m_rotation->x != x || m_rotation->y != y || m_rotation->z != z)
        {
            m_rotation->Set(x, y, z);
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetRotation(const Liar::Vector3D& v)
    {
        SetRotation(v.x, v.y, v.z);
    }
    
    // ======================== change Scale ==========================
    void LiarDisplayObject::SetScaleX(float v)
    {
        if (m_scale->x != v)
        {
            m_scale->x = v;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetScaleY(float v)
    {
        if (m_scale->y != v)
        {
            m_scale->y = v;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetScaleZ(float v)
    {
        if (m_scale->z != v)
        {
            m_scale->z = v;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetScale(float scale)
    {
        SetScale(scale, scale, scale);
    }
    
    void LiarDisplayObject::SetScale(float x, float y, float z)
    {
        if (m_scale->x != x || m_scale->y != y || m_scale->z != z)
        {
            m_scale->Set(x, y, z);
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::SetScale(const Liar::Vector3D& v)
    {
        SetScale(v.x, v.y, v.z);
    }
    
    void LiarDisplayObject::AddX(float x)
    {
        if(x != 0)
        {
            m_rotation->x += x;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddY(float y)
    {
        if(y != 0)
        {
            m_position->y += y;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddZ(float z)
    {
        if(z != 0)
        {
            m_position->z += z;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddPosition(float x, float y, float z)
    {
        if(x != 0 || y != 0 || z != 0)
        {
            m_position->x += x;
            m_position->y += y;
            m_position->z += z;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddPosition(const Liar::Vector3D& v)
    {
        AddPosition(v.x, v.y, v.z);
    }
    
    void LiarDisplayObject::AddScaleX(float x)
    {
        if(x != 0)
        {
            m_scale->x += x;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddScaleY(float y)
    {
        if(y != 0)
        {
            m_scale->y += y;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddScaleZ(float z)
    {
        if(z != 0)
        {
            m_scale->z += z;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddScale(float x, float y, float z)
    {
        if(x != 0 || y != 0 || z != 0)
        {
            m_scale->x += x;
            m_scale->y += y;
            m_scale->z += z;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddScale(const Liar::Vector3D& v)
    {
        AddScale(v.x, v.y, v.z);
    }
    
    void LiarDisplayObject::AddRotationX(float x)
    {
        if(x != 0)
        {
            m_rotation->x += x;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddRotationY(float y)
    {
        if(y != 0)
        {
            m_rotation->y += y;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddRotationZ(float z)
    {
        if(z != 0)
        {
            m_rotation->z += z;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddRotation(float x, float y, float z)
    {
        if(x != 0 || y != 0 || z != 0)
        {
            m_rotation->x += x;
            m_rotation->y += y;
            m_rotation->z += z;
            m_transformChanged = true;
        }
    }
    
    void LiarDisplayObject::AddRotation(const Liar::Vector3D& v)
    {
        AddRotation(v.x, v.y, v.z);
    }
    
	LiarContainerObject::LiarContainerObject()
		:Liar::LiarDisplayObject()
	{
	}


	LiarContainerObject::~LiarContainerObject()
	{
	}
    
    // ================= Child =================
    Liar::LiarDisplayObject* LiarContainerObject::AddChild(Liar::LiarDisplayObject * child)
    {
        if(!child)
        {
            std::cout << "Add nullptr ERROR!!" << std::endl;
            return nullptr;
        }
		if (child->GetParent() == this) return child;
		if (child->GetParent()) child->GetParent()->RemoveChild(child);
        child->SetParent(this);
        if(!m_childrenNode)
        {
            m_childrenNode = child;
        }
        else
        {
            Liar::LiarContainerObject* current = static_cast<Liar::LiarContainerObject*>(m_childrenNode);
			while (current)
			{
				if (!current->m_nextChildNode)
				{
					current->m_nextChildNode = child;
					break;
				}
				current = static_cast<Liar::LiarContainerObject*>(current->m_nextChildNode);
			}
        }
 
        return child;
    }
    
    Liar::LiarDisplayObject* LiarContainerObject::RemoveChild(Liar::LiarDisplayObject* child)
    {
        bool find = false;
        if(m_childrenNode)
        {
			Liar::LiarDisplayObject* pre = nullptr;
			Liar::LiarDisplayObject* current = m_childrenNode;
			while (!find &&  current)
			{
				if (current == child)
				{
					if (pre)
					{
						pre->SetNextChildNode(current->GetNextChildNode());
					}
					else
					{
						m_childrenNode = current->GetNextChildNode();
					}
					find = true;
					break;
				}
				current->SetNextChildNode(nullptr);
				pre = current;
				current = current->GetNextChildNode();
			}
        }
        
        if(find)
        {
            child->SetParent(nullptr);
            return child;
        }
        else
        {
            return nullptr;
        }
    }
    
    Liar::LiarDisplayObject* LiarContainerObject::RemoveChild(const std::string& name)
    {
        Liar::LiarDisplayObject* findNode = nullptr;
        if(m_childrenNode)
        {
			Liar::LiarDisplayObject* pre = nullptr;
			Liar::LiarDisplayObject* current = m_childrenNode;
			while (current)
			{
				if (current->GetName() == name)
				{
					if (pre)
					{
						pre->SetNextChildNode(current->GetNextChildNode());
					}
					else
					{
						m_childrenNode = current->GetNextChildNode();
					}
					findNode = current;
					break;
				}
				current->SetNextChildNode(nullptr);
				pre = current;
				current = current->GetNextChildNode();
			}
        }
        
        if(findNode)
        {
            findNode->SetParent(nullptr);
        }
        return findNode;
    }
    
    bool LiarDisplayObject::CalcTransform(bool combineParent, bool calcInvert)
    {
        if (m_transformChanged || (combineParent && m_parent))
        {
            m_transform->Identity();
            m_transform->Scale(*m_scale);
            m_transform->Rotate(*m_rotation);
            m_transform->Translate(*m_position);

			if(m_parent) (*m_transform) *= (*(m_parent->GetTransform()));

            m_transformChanged = false;
        }

		return true;
    }
    
    bool LiarDisplayObject::Render(Liar::LiarShaderProgram& shader, bool combineParent)
    {
        bool calcResult = CalcTransform(combineParent);
		shader.SetMat4("model", *m_transform);
		return calcResult;
    }
    
    // ====================== container =========================== //
    bool LiarContainerObject::RemoveAndDisposeChild(Liar::LiarDisplayObject* child)
    {
        Liar::LiarDisplayObject* findChild = RemoveChild(child);
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
    
    bool LiarContainerObject::RemoveAndDisposeChild(const std::string& name)
    {
        Liar::LiarDisplayObject* findChild = RemoveChild(name);
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
    bool LiarContainerObject::Render(Liar::LiarShaderProgram& shader, bool combineParent)
    {
        bool calcResult = Liar::LiarDisplayObject::Render(shader, combineParent);
        RenderChildren(shader, calcResult);
		return calcResult;
    }
    
    void LiarContainerObject::RenderChildren(Liar::LiarShaderProgram& shader, bool combineParent)
    {
        Liar::LiarDisplayObject* child = m_childrenNode;
        while (child)
        {
            child->Render(shader, combineParent);
            child = child->GetNextChildNode();
        }
    }

	std::ostream& operator<<(std::ostream& os, const Liar::LiarContainerObject& m)
	{
		os << "position(x:" << m.m_position->x << "," << m.m_position->y << "," << m.m_position->z << "),\n";
		os << "rotation(x:" << m.m_rotation->x << "," << m.m_rotation->y << "," << m.m_rotation->z << "),\n";
		os << "scale(x:" << m.m_scale->x << "," << m.m_scale->y << "," << m.m_scale->z << "),\n";
		return os;
	}

	///////////////////////////////////////////////////////////////////////////////
	// draw the local axis of an object
	///////////////////////////////////////////////////////////////////////////////
	void LiarContainerObject::DrawAxis(float size)
	{
		
	}

}
