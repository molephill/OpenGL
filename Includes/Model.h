#pragma once

#include "Entity.h"
#include <LiarMesh.h>

namespace Liar
{
	class Model:public Entity
	{
	public:
		Model();
		~Model();

	private:
		std::vector<Liar::LiarMesh*>* m_subMeshList;

	public:
		void AddMesh(const char*, const char* base=nullptr);
		void AddMesh(const std::string&, const char* base=nullptr);
		void AddMesh(Liar::LiarMesh* subMesh) { m_subMeshList->push_back(subMesh); };

		virtual void Render(Liar::Shader&);

		friend std::ostream& operator<<(std::ostream& os, const Liar::Model& m);
	};
}

