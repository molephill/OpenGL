//
//  AssetsMgr.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "AssetsMgr.hpp"

namespace Liar
{
    AssetsMgr::AssetsMgr():m_allTexContexts(nullptr),m_allMeshes(nullptr)
    {
    }
    
    AssetsMgr::~AssetsMgr()
    {
    }

	Liar::LiarMesh* AssetsMgr::GetMesh(const char* fileName, const char* base)
	{
		if (!m_allMeshes) m_allMeshes = new std::vector<Liar::LiarMesh*>();
		size_t len = m_allMeshes->size();
		Liar::LiarMesh* ret = nullptr;
		for (size_t i = 0; i < len; i++)
		{
			Liar::LiarMesh* mesh = m_allMeshes->at(i);
			if (std::strcmp(fileName, mesh->meshName.data()) == 0)
			{
				ret = mesh;
				break;
			}
		}

		if (ret == nullptr)
		{
			ret = Liar::LiarPluginRead::ReadMesh(fileName, base);
			ret->meshName = fileName;
			ret->Upload();
			m_allMeshes->push_back(ret);
		}

		ret->AddRef();
		
		return ret;
	}

	Liar::LiarMesh* AssetsMgr::GetMesh(const std::string& fileName, const char* base)
	{
		return GetMesh(fileName.data(), base);
	}

	Liar::LiarTexContext* AssetsMgr::GetTexContext(const char* fileName)
	{
		if (!m_allTexContexts) m_allTexContexts = new std::vector<Liar::LiarTexContext*>();
		size_t len = m_allTexContexts->size();
		Liar::LiarTexContext* ret = nullptr;
		for (size_t i = 0; i < len; ++i)
		{
			Liar::LiarTexContext* textContext = m_allTexContexts->at(i);
			if (std::strcmp(fileName, textContext->GetPath().data()) == 0)
			{
				ret = textContext;
				break;
			}
		}
        
		if (ret == nullptr)
        {
            ret = new Liar::LiarTexContext();
			ret->Upload(fileName);
			ret->AddRef();
			m_allTexContexts->push_back(ret);
		}

		return ret;
	}

	Liar::LiarTexContext* AssetsMgr::GetTexContext(const std::string& fileName)
	{
		return GetTexContext(fileName.data());
	}
    
    std::string AssetsMgr::GetPath(const char* base)
    {
        return "" + BASE_PATH + base;
    }
    
    void AssetsMgr::PrintMat4(const glm::mat4 & view)
    {
        std::cout << std::fixed << std::setprecision(5);
        std::cout << "[" << std::setw(10) << view[0][0] << " " << std::setw(10) << view[0][1] << " " << std::setw(10) << view[0][2] << " " << std::setw(10) << view[0][3] << "]\n"
        << "[" << std::setw(10) << view[1][0] << " " << std::setw(10) << view[1][1] << " " << std::setw(10) << view[1][2] << " " << std::setw(10) << view[1][3] << "]\n"
        << "[" << std::setw(10) << view[2][0] << " " << std::setw(10) << view[2][1] << " " << std::setw(10) << view[2][2] << " " << std::setw(10) << view[2][3] << "]\n"
        << "[" << std::setw(10) << view[3][0] << " " << std::setw(10) << view[3][1] << " " <<std::setw(10) << view[3][2] << " " << std::setw(10) << view[3][3] << "]\n";
        std::cout << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
    }

	AssetsMgr* AssetsMgr::m_instance = nullptr;
}
