#pragma once

#include "LiarObjects.h"
#include <LiarMesh.h>
#include <LiarSkeleton.h>

namespace Liar
{
	class Model:public LiarContainerObject
	{
	public:
		Model();
		~Model();

	private:
		std::vector<Liar::LiarMesh*>* m_subMeshList;
		Liar::LiarSkeleton* m_skeleton;

	private:
		void LoadSub(const Liar::LiarNode&, const char* base = nullptr);

	public:
		void Load(const char*);
		virtual void Render(Liar::LiarShaderProgram&);

		friend std::ostream& operator<<(std::ostream& os, const Liar::Model& m);
	};
}

