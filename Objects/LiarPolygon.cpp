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

		m_indiceSize = m_indices->size();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// 3. 设定顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}

	LiarCube::LiarCube() :
		Liar::LiarMesh()
	{
		m_geometry = Liar::LiarPolygonGeoMgr::GetGeo(Liar::LiarPolygonGeometryType::GeometryType_Cube);
	}

	LiarCube::~LiarCube()
	{
		Liar::LiarPolygonGeoMgr::ReleaseGeo(Liar::LiarPolygonGeometryType::GeometryType_Cube);
		m_geometry = nullptr;
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
				//vertices.push_back(nx);
				//vertices.push_back(ny);
				//vertices.push_back(nz);

				//// vertex tex coord
				//s = (float)j / sectorCount;
				//t = (float)i / stackCount;
				//vertices.push_back(s);
				//vertices.push_back(t);
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

		m_indiceSize = m_indices->size();

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		// 3. 设定顶点属性指针
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
	}

	// ====================== rectSprit =======================
	void LiarRectSpriteGeometry::UploadSub()
	{
		float vertices[] = {
			// positions          // colors           // texture coords
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
		};

		m_indices->push_back(0);
		m_indices->push_back(1);
		m_indices->push_back(3);
		m_indices->push_back(1);
		m_indices->push_back(2);
		m_indices->push_back(3);

		m_indiceSize = m_indices->size();

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// texture coord attribute
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	LiarSphere::LiarSphere() :
		Liar::LiarMesh()
	{
		m_geometry = LiarPolygonGeoMgr::GetGeo(Liar::LiarPolygonGeometryType::GeometryType_Sphere);
	}

	LiarSphere::~LiarSphere()
	{
		LiarPolygonGeoMgr::ReleaseGeo(Liar::LiarPolygonGeometryType::GeometryType_Sphere);
		m_geometry = nullptr;
	}

	// ======================== geom_mgr ===================
	LiarGeometry* LiarPolygonGeoMgr::GetGeo(Liar::LiarPolygonGeometryType type)
	{
		switch (type)
		{
		case Liar::LiarPolygonGeometryType::GeometryType_Cube:
		{
			if (!m_cubeGeo)
			{
				m_cubeGeo = new Liar::LiarCubeGeometry();
				m_cubeGeo->Upload();
			}
			m_cubeGeo->IncRefCount();
			return m_cubeGeo;
		}
		case Liar::LiarPolygonGeometryType::GeometryType_Sphere:
		{
			if (!m_sphereGeo)
			{
				m_sphereGeo = new Liar::LiarSphereGeometry();
				m_sphereGeo->Upload();
			}

			m_sphereGeo->IncRefCount();
			return m_sphereGeo;
		}
		case Liar::LiarPolygonGeometryType::GeometryType_RectSprite:
		{
			if (!m_rectSpriteGeo)
			{
				m_rectSpriteGeo = new Liar::LiarRectSpriteGeometry();
				m_rectSpriteGeo->Upload();
			}
			m_rectSpriteGeo->IncRefCount();
			return m_rectSpriteGeo;
		}
		default:
			return nullptr;
		}
	}

	void LiarPolygonGeoMgr::ReleaseGeo(Liar::LiarPolygonGeometryType type)
	{
		Liar::LiarGeometry* ret = nullptr;
		switch (type)
		{
		case Liar::LiarPolygonGeometryType::GeometryType_Cube:
			ret = m_cubeGeo;
			break;
		case Liar::LiarPolygonGeometryType::GeometryType_Sphere:
			ret = m_sphereGeo;
			break;
		case Liar::LiarPolygonGeometryType::GeometryType_RectSprite:
			ret = m_rectSpriteGeo;
			break;
		default:
			break;
		}

		if (ret)
		{
			if (ret->DesRefCount() <= 0)
			{
				delete ret;
				ret = nullptr;
			}
		}
	}

	Liar::LiarCubeGeometry* LiarPolygonGeoMgr::m_cubeGeo = nullptr;
	Liar::LiarSphereGeometry* LiarPolygonGeoMgr::m_sphereGeo = nullptr;
	Liar::LiarRectSpriteGeometry* LiarPolygonGeoMgr::m_rectSpriteGeo = nullptr;
}
