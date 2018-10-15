#pragma once
#include <PluginDefine.h>
#include <LiarStringUtil.h>
#include <LiarMaterial.h>
#include <LiarSkeleton.h>
#include <LiarSkeletonAnim.h>
#include <LiarGeometries.h>
#include <LiarRefrence.h>

#include "Camera3D.h"

namespace Liar
{
	class LiarMesh:public Liar::LiarContainerObject, public LiarReference
	{
	public:
		LiarMesh();
		~LiarMesh();

	protected:
		Liar::LiarGeometry* m_geometry;
		std::vector<Liar::LiarMaterial*>* m_materials;

	public:
		void Load(const char*, const char* base = nullptr);

		bool SetGeometry(Liar::LiarGeometry*);
		Liar::LiarGeometry* GetGeo() { return m_geometry; };

		std::vector<Liar::LiarMaterial*>* GetMatrials() { return m_materials; };
		Liar::LiarMaterial* GetMat(size_t index) { return m_materials->at(index); };

		void EraseMaterial(int);

		std::string meshName;

	public:
		friend std::ostream& operator<<(std::ostream& os, const Liar::LiarMesh& m);

	public:
		virtual bool Render(Liar::LiarShaderProgram&, bool combineParent = false);

	};
}

