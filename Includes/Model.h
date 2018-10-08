#pragma once

#include "LiarContainerObject.h"
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

	public:
		void AddMesh(const char*, const char* base=nullptr);
		void AddMesh(const std::string&, const char* base=nullptr);
		void AddMesh(Liar::LiarMesh* subMesh) { m_subMeshList->push_back(subMesh); };

		void SetSkeleton(const char*);
		void SetSkeleton(const std::string&);

		virtual void Render(Liar::LiarShaderProgram&);

		friend std::ostream& operator<<(std::ostream& os, const Liar::Model& m);
	};
}

