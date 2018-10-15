#pragma once
#include <LiarMesh.h>

namespace Liar
{
	enum LiarPolygonGeometryType
	{
		GeometryType_Cube = 0x0,
		GeometryType_Sphere = 0x1,
		GeometryType_RectSprite = 0x2,
	};

	class LiarPolygonGeometry :public Liar::LiarGeometry
	{
	public:
		LiarPolygonGeometry() :m_indices(new std::vector<int>()) {};
		~LiarPolygonGeometry() {};

	protected:
		std::vector<int>* m_indices;

		virtual int GetIndicesSize() const 
		{
			return m_indices->size();
		};

		virtual std::vector<int>* GetIndicesData() const
		{
			return m_indices;
		};

		virtual void ReleaseSourceData()
		{
			delete m_indices;
		}
	};

	class LiarCubeGeometry :public Liar::LiarPolygonGeometry
	{
	public:
		LiarCubeGeometry() :Liar::LiarPolygonGeometry() {};
		virtual ~LiarCubeGeometry() {};

	protected:
		virtual void UploadSub();
	};

	// ==================== sphere ===================
	class LiarSphereGeometry :public Liar::LiarPolygonGeometry
	{
	public:
		LiarSphereGeometry() :Liar::LiarPolygonGeometry() {};
		virtual ~LiarSphereGeometry() {};

	protected:
		virtual void UploadSub();
	};

	class LiarRectSpriteGeometry :public Liar::LiarPolygonGeometry
	{
	public:
		LiarRectSpriteGeometry() :Liar::LiarPolygonGeometry() {};
		virtual ~LiarRectSpriteGeometry() {};

	protected:
		virtual void UploadSub();
	};

	class LiarPolygonGeoMgr
	{
	private:
		static Liar::LiarCubeGeometry* m_cubeGeo;
		static Liar::LiarSphereGeometry* m_sphereGeo;
		static Liar::LiarRectSpriteGeometry* m_rectSpriteGeo;

	public:
		static LiarGeometry* GetGeo(Liar::LiarPolygonGeometryType);
		static void ReleaseGeo(Liar::LiarPolygonGeometryType);
	};

	class LiarCube:public Liar::LiarMesh
	{
	public:
		LiarCube();
		~LiarCube();
	};

	class LiarSphere :public Liar::LiarMesh
	{
	public:
		LiarSphere();
		~LiarSphere();
	};
}
