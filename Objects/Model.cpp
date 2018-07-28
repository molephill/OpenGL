#include "Model.h"
#include "AssetsMgr.hpp"


namespace Liar
{
	Model::Model():
		m_subMeshList(new std::vector<Liar::LiarMesh*>())
	{
	}


	Model::~Model()
	{
	}

	void Model::AddMesh(const char* fileName)
	{
		Liar::LiarMesh* ret = Liar::AssetsMgr::GetInstance().GetMesh(fileName);
		m_subMeshList->push_back(ret);
	}

	void Model::AddMesh(const std::string& fileName)
	{
		AddMesh(fileName.data());
	}

	void Model::Render(Liar::Shader& shader)
	{
		AddRotationY(1.0f);

		CalcTransform();
		shader.SetMat4("model", *m_transform);

		size_t len = m_subMeshList->size();
		for (size_t i = 0; i < len; ++i)
		{
			Liar::LiarMesh* mesh = m_subMeshList->at(i);
			mesh->Render(shader);
		}
	}
}
