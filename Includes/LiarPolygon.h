#pragma once
#include <LiarMesh.h>

namespace Liar
{
	class LiarCubeGeometry :public Liar::LiarBaseGeometry, public Liar::ILiarRef
	{
	protected:
		virtual void UploadSub();
	};

	// ==================== sphere ===================
	class LiarSphereGeometry :public Liar::LiarBaseGeometry, public Liar::ILiarRef
	{
	protected:
		virtual void UploadSub();
	};

	class LiarPolygonGeoMgr
	{
	private:
		static Liar::LiarCubeGeometry* m_cubeGeo;
		static Liar::LiarSphereGeometry* m_sphereGeo;

	public:
		static LiarCubeGeometry* GetCubeGeo();
		static LiarSphereGeometry* GetSphereGeo();
		static void ReleaseCubeGeo();
		static void ReleaseSphereGeo();
	};

	class LiarCube:public Liar::LiarDisplayObject
	{
	public:
		LiarCube();
		~LiarCube();

	protected:
		Liar::LiarCubeGeometry* m_geometry;

	public:
		virtual void Render(Liar::LiarShaderProgram&);
	};

	class LiarSphere :public Liar::LiarDisplayObject
	{
	public:
		LiarSphere();
		~LiarSphere();

	protected:
		Liar::LiarSphereGeometry* m_geometry;

	public:
		virtual void Render(Liar::LiarShaderProgram&);
	};
}
