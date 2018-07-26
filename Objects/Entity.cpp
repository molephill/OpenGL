#include "Entity.h"

namespace Liar
{
	Entity::Entity()
		:m_x(0.0f),m_y(0.0f),m_z(0.0f)
		, m_rotationX(0.0f), m_rotationY(0.0f), m_rotationZ(0.0f)
		, m_scaleX(1.0f), m_scaleY(1.0f), m_scaleZ(1.0f)
		, m_transformChanged(true)
		, m_parent(nullptr), m_childrenList(nullptr)
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
		if (v.x != m_x || v.y != m_y || v.z != m_z)
		{
			m_x = v.x;
			m_y = v.y;
			m_z = v.z;
			m_transformChanged = true;
		}
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
		if (v.x != m_rotationX || v.y != m_rotationY || v.z != m_rotationZ)
		{
			m_rotationX = v.x;
			m_rotationY = v.y;
			m_rotationZ = v.z;
			m_transformChanged = true;
		}
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

	void Entity::SetScale(float x, float y, float z)
	{
		if (m_scaleX != x || m_scaleY != y || m_scaleZ)
		{
			m_scaleX = x;
			m_scaleY = y;
			m_scaleZ = z;
			m_transformChanged = true;
		}
	}

	void Entity::SetScale(const Liar::Vector3D& v)
	{
		if (v.x != m_scaleX || v.y != m_scaleY || v.z != m_scaleZ)
		{
			m_scaleX = v.x;
			m_scaleY = v.y;
			m_scaleZ = v.z;
			m_transformChanged = true;
		}
	}

	// ================== render ==================
	void Entity::CalcTransform(bool calcInvert)
	{
		if (m_transformChanged)
		{

			m_transformChanged = false;
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// draw the local axis of an object
	///////////////////////////////////////////////////////////////////////////////
	void Entity::DrawAxis(float size)
	{
		//glDepthFunc(GL_ALWAYS);     // to avoid visual artifacts with grid lines
		//glDisable(GL_LIGHTING);
		//glPushMatrix();             //NOTE: There is a bug on Mac misbehaviours of
		//							//      the light position when you draw GL_LINES
		//							//      and GL_POINTS. remember the matrix.

		//							// draw axis
		//glLineWidth(3);
		//glBegin(GL_LINES);
		//glColor3f(1, 0, 0);
		//glVertex3f(0, 0, 0);
		//glVertex3f(size, 0, 0);
		//glColor3f(0, 1, 0);
		//glVertex3f(0, 0, 0);
		//glVertex3f(0, size, 0);
		//glColor3f(0, 0, 1);
		//glVertex3f(0, 0, 0);
		//glVertex3f(0, 0, size);
		//glEnd();
		//glLineWidth(1);

		//// draw arrows(actually big square dots)
		//glPointSize(5);
		//glBegin(GL_POINTS);
		//glColor3f(1, 0, 0);
		//glVertex3f(size, 0, 0);
		//glColor3f(0, 1, 0);
		//glVertex3f(0, size, 0);
		//glColor3f(0, 0, 1);
		//glVertex3f(0, 0, size);
		//glEnd();
		//glPointSize(1);

		//// restore default settings
		//glPopMatrix();
		//glEnable(GL_LIGHTING);
		//glDepthFunc(GL_LEQUAL);
	}

}