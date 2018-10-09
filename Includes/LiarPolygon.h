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

	class LiarCubeGeometry :public Liar::LiarBaseGeometry
	{
	public:
		LiarCubeGeometry() :Liar::LiarBaseGeometry() {};
		virtual ~LiarCubeGeometry() {};

	protected:
		virtual void UploadSub();
	};

	// ==================== sphere ===================
	class LiarSphereGeometry :public Liar::LiarBaseGeometry
	{
	public:
		LiarSphereGeometry() :Liar::LiarBaseGeometry() {};
		virtual ~LiarSphereGeometry() {};

	protected:
		virtual void UploadSub();
	};

	class LiarRectSpriteGeometry :public Liar::LiarBaseGeometry
	{
	public:
		LiarRectSpriteGeometry() :Liar::LiarBaseGeometry() {};
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
		static LiarBaseGeometry* GetGeo(Liar::LiarPolygonGeometryType);
		static void ReleaseGeo(Liar::LiarPolygonGeometryType);
	};

	class LiarCube:public Liar::LiarDisplayObject
	{
	public:
		LiarCube();
		~LiarCube();

	protected:
		Liar::LiarBaseGeometry* m_geometry;

	public:
		virtual void Render(Liar::LiarShaderProgram&);
	};

	class LiarSphere :public Liar::LiarDisplayObject
	{
	public:
		LiarSphere();
		~LiarSphere();

	protected:
		Liar::LiarBaseGeometry* m_geometry;

	public:
		virtual void Render(Liar::LiarShaderProgram&);
	};
}
