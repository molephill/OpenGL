#include "Model.h"
#include "AssetsMgr.hpp"

namespace Liar
{
	Model::Model():
		Liar::LiarContainerObject(),
		m_subMeshList(new std::vector<Liar::LiarMesh*>()),
		m_skeleton(nullptr)
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

	void Model::SetSkeleton(const char* path)
	{
		m_skeleton = Liar::AssetsMgr::GetInstance().GetSkeleton(path);
	}

	void Model::SetSkeleton(const std::string& path)
	{
		SetSkeleton(path.c_str());
	}

	void Model::Render(Liar::LiarShaderProgram& shader)
	{
		/*AddRotationY(1.0f);*/
		//AddRotation(0.0f, 1.0f, 0.0f);
        
        Liar::LiarContainerObject::Render(shader);
        
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
