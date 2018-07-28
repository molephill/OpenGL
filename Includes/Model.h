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
		void AddMesh(const char*);
		void AddMesh(const std::string&);
		void Render(Liar::Shader&);
	};
}

