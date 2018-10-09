#include "LiarPolygon.h"
#include <PluginDefine.h>

namespace Liar
{
	void LiarCubeGeometry::UploadSub()
	{
		float l = 0.5f;
		float w = 0.5f;
		float h = 0.5f;

		float vertices[] = {
			-l, -w, -h,
			l, -w, -h,
			-l, w, -h,
			l, w, -h,

			-l, -w, h,
			l, -w, h,
			-l, w, h,
			l, w, h
		};

		m_indices->push_back(0);
		m_indices->push_back(2);
		m_indices->push_back(3);
		m_indices->push_back(3);
		m_indices->push_back(1);
		m_indices->push_back(0);

		m_indices->push_back(4);
		m_indices->push_back(5);
		m_indices->push_back(7);
		m_indices->push_back(7);
		m_indices->push_back(6);
		m_indices->push_back(4);

		m_indices->push_back(0);
		m_indices->push_back(1);
		m_indices->push_back(5);
		m_indices->push_back(5);
		m_indices->push_back(4);
		m_indices->push_back(0);

		m_indices->push_back(1);
		m_indices->push_back(3);
		m_indices->push_back(7);
		m_indices->push_back(7);
		m_indices->push_back(5);
		m_indices->push_back(1);

		m_indices->push_back(3);
		m_indices->push_back(2);
		m_indices->push_back(6);
		m_indices->push_back(6);
		m_indices->push_back(7);
		m_indices->push_back(3);

		m_indices->push_back(2);
		m_indices->push_back(0);
		m_indices->push_back(4);
		m_indices->push_back(4);
		m_indices->push_back(6);
		m_indices->push_back(2);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 3. 设定顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}

	LiarCube::LiarCube() :
		Liar::LiarDisplayObject()
	{
		m_geometry = LiarPolygonGeoMgr::GetCubeGeo();
		m_geometry->Upload();
	}

	LiarCube::~LiarCube()
	{
		LiarPolygonGeoMgr::ReleaseCubeGeo();
		m_geometry = nullptr;
	}

	void LiarCube::Render(Liar::LiarShaderProgram& shader)
	{
		Liar::LiarDisplayObject::Render(shader);
		m_geometry->Render();
	}

	// =============================== sphere ===============================
	void LiarSphereGeometry::UploadSub()
	{
		float radius = 0.5f;
		int sectorCount = 36;
		int stackCount = 18;

		float x, y, z, xy;                              // vertex position
		//float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
		//float s, t;                                     // texCoord

		float sectorStep = 2 * PI / sectorCount;
		float stackStep = PI / stackCount;
		float sectorAngle, stackAngle;

		std::vector<float> vertices;

		for (int i = 0; i <= stackCount; ++i)
		{
			stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
			xy = radius * cosf(stackAngle);             // r * cos(u)
			z = radius * sinf(stackAngle);              // r * sin(u)

														// add (sectorCount+1) vertices per stack
														// the first and last vertices have same position and normal, but different tex coods
			for (int j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep;

				// vertex position
				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);

				// vertex normal
				//nx = x * lengthInv;
				//ny = y * lengthInv;
				//nz = z * lengthInv;
				//normals.push_back(nx);
				//normals.push_back(ny);
				//normals.push_back(nz);

				//// vertex tex coord
				//s = (float)j / sectorCount;
				//t = (float)i / stackCount;
				//texCoords.push_back(s);
				//texCoords.push_back(t);
			}
		}

		// indices
		unsigned int k1, k2;
		for (int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);     // bebinning of current stack
			k2 = k1 + sectorCount + 1;      // beginning of next stack

			for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding 1st and last stacks
				if (i != 0)
				{
					m_indices->push_back(k1);
					m_indices->push_back(k2);
					m_indices->push_back(k1 + 1);
				}

				if (i != (stackCount - 1))
				{
					m_indices->push_back(k1 + 1);
					m_indices->push_back(k2);
					m_indices->push_back(k2 + 1);
				}
			}
		}

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		// 3. 设定顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}

	LiarSphere::LiarSphere() :
		Liar::LiarDisplayObject()
	{
		m_geometry = LiarPolygonGeoMgr::GetSphereGeo();
		m_geometry->Upload();
	}

	LiarSphere::~LiarSphere()
	{
		LiarPolygonGeoMgr::ReleaseSphereGeo();
		m_geometry = nullptr;
	}

	void LiarSphere::Render(Liar::LiarShaderProgram& shader)
	{
		Liar::LiarDisplayObject::Render(shader);
		m_geometry->Render();
	}

	// ======================== geom_mgr ===================
	LiarCubeGeometry* LiarPolygonGeoMgr::GetCubeGeo()
	{
		if (!m_cubeGeo)
		{
			m_cubeGeo = new Liar::LiarCubeGeometry();
			m_cubeGeo->Upload();
		}
		m_cubeGeo->IncRefCount();
		return m_cubeGeo;
	}

	LiarSphereGeometry* LiarPolygonGeoMgr::GetSphereGeo()
	{
		if (!m_sphereGeo)
		{
			m_sphereGeo = new Liar::LiarSphereGeometry();
			m_sphereGeo->Upload();
		}

		m_sphereGeo->IncRefCount();
		return m_sphereGeo;
	}

	void LiarPolygonGeoMgr::ReleaseCubeGeo()
	{
		if (m_cubeGeo)
		{
			if (m_cubeGeo->DesRefCount() <= 0)
			{
				delete m_cubeGeo;
				m_cubeGeo = nullptr;
			}
		}
	}

	void LiarPolygonGeoMgr::ReleaseSphereGeo()
	{
		if (m_sphereGeo)
		{
			if (m_sphereGeo->DesRefCount() <= 0)
			{
				delete m_sphereGeo;
				m_sphereGeo = nullptr;
			}
		}
	}

	Liar::LiarCubeGeometry* LiarPolygonGeoMgr::m_cubeGeo = nullptr;
	Liar::LiarSphereGeometry* LiarPolygonGeoMgr::m_sphereGeo = nullptr;
}
