#include "LiarModel.h"
#include "AssetsMgr.hpp"
#include <LiarStringUtil.h>

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

	void Model::Load(const char* path)
	{
		Liar::LiarNode* node = new Liar::LiarNode();
		Liar::LiarPluginRead::ReadNode(path, *node);
		std::string szPath(path);
		std::string basePath = Liar::StringUtil::GetHead(szPath, "/") + "/";
		LoadSub(*node, basePath.c_str());
		delete node;
	}

	void Model::LoadSub(const Liar::LiarNode& node, const char* base)
	{
		std::vector<Liar::LiarNode*>* children = node.GetChildren();
		if (children)
		{
			size_t size = children->size();
			for (size_t i = 0; i < size; ++i)
			{
				Liar::LiarNode* subNode = children->at(i);
				std::string& nodeName = subNode->GetNodeName();

				Liar::LiarMesh* subMesh = new Liar::LiarMesh();
				subMesh->SetParent(this);
				subMesh->Load(nodeName.c_str(), base);
				m_subMeshList->push_back(subMesh);

				// add child nodes
				LoadSub(*subNode);
			}
		}
	}

	bool Model::Render(Liar::LiarShaderProgram& shader, bool combineParent)
	{
        bool calcResult = Liar::LiarContainerObject::Render(shader, combineParent);
        
		size_t len = m_subMeshList->size();
		for (size_t i = 0; i < len; ++i)
		{
			Liar::LiarMesh* mesh = m_subMeshList->at(i);
			mesh->Render(shader, calcResult);
		}

		return calcResult;
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
