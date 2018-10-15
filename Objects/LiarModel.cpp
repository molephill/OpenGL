#include "LiarModel.h"
#include "AssetsMgr.hpp"
#include <LiarStringUtil.h>

namespace Liar
{
	Model::Model():
		Liar::LiarContainerObject(),
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
				subMesh->Load(nodeName.c_str(), base);
				subMesh->SetName(m_name + "_sub_" + std::to_string(i));
				AddChild(subMesh);

				// add child nodes
				LoadSub(*subNode);
			}
		}
	}
}
