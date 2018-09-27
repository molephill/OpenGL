#include "Model.h"
#include "AssetsMgr.hpp"

namespace Liar
{
	Model::Model():
		Liar::Entity(),
		m_subMeshList(new std::vector<Liar::LiarMesh*>())
	{
	}


	Model::~Model()
	{
	}

	void Model::AddMesh(const char* fileName, const char* base)
	{
		Liar::LiarMesh* ret = Liar::AssetsMgr::GetInstance().GetMesh(fileName, base);
		m_subMeshList->push_back(ret);
	}

	void Model::AddMesh(const std::string& fileName, const char* base)
	{
		AddMesh(fileName.c_str(), base);
	}

	void Model::Render(Liar::LiarShaderProgram& shader)
	{
		/*AddRotationY(1.0f);*/
		//AddRotation(0.0f, 1.0f, 0.0f);
        
        Liar::Entity::Render(shader);
        
		size_t len = m_subMeshList->size();
		for (size_t i = 0; i < len; ++i)
		{
			Liar::LiarMesh* mesh = m_subMeshList->at(i);
			mesh->Render(shader);
		}
	}

	std::ostream& operator<<(std::ostream& os, const Liar::Model& m)
	{
		size_t len = m.m_subMeshList->size();
		os << "mesh size:" << len << "\n";
		for (size_t i = 0; i < len; ++i)
		{
			os << "sub mesh info:\n" << *(m.m_subMeshList->at(i)) << "\n";
		}
		return os;
	}
}
