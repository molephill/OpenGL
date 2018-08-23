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

	Liar::LiarMesh* AssetsMgr::GetMeshByObj(const char* fileName, const char* base)
	{
		Liar::LiarMesh* mesh = new Liar::LiarMesh();

		std::vector<Liar::Vector3D*>* positions = new std::vector<Liar::Vector3D*>();
		std::vector<Liar::Vector3D*>* normals = new std::vector<Liar::Vector3D*>();
		std::vector<Liar::Vector3D*>* texcoords = new std::vector<Liar::Vector3D*>();

		float tmpx = 0.0f, tmpy = 0.0f, tmpz = 0.0f;

		std::ifstream ssFileContent(fileName);
		char szOneLine[256];
		std::string temp;
		while (!ssFileContent.eof())
		{
			memset(szOneLine, 0, 256);
			ssFileContent.getline(szOneLine, 256);
			if (strlen(szOneLine)>0)
			{
				std::stringstream ssOneLine(szOneLine);
				if (szOneLine[0] == 'v')//解析顶点信息
				{

					if (szOneLine[1] == 't')//解析纹理坐标
					{
						ssOneLine >> temp;//vt
						ssOneLine >> tmpx;
						ssOneLine >> tmpy;
						Liar::Vector3D* vi = new Liar::Vector3D(tmpx, tmpy, 0.0f);
						texcoords->push_back(vi);
					}
					else if (szOneLine[1] == 'n')//解析法线坐标
					{
						ssOneLine >> temp;//vn
						ssOneLine >> tmpx;
						ssOneLine >> tmpy;
						ssOneLine >> tmpz;
						Liar::Vector3D* vi = new Liar::Vector3D(tmpx, tmpy, tmpz);
						normals->push_back(vi);
					}
					else //解析顶点信息
					{
						ssOneLine >> temp;//v
						ssOneLine >> tmpx;
						ssOneLine >> tmpy;
						ssOneLine >> tmpz;
						Liar::Vector3D* vi = new Liar::Vector3D(tmpx, tmpy, tmpz);
						positions->push_back(vi);
					}
				}
				else if (szOneLine[0] == 'f') //解析面信息
				{
					ssOneLine >> temp;//f
					std::string vertexStr;
					for (int i = 0; i < 3; ++i)
					{
						ssOneLine >> vertexStr;
						size_t pos = vertexStr.find_first_of('/');
						std::string positionIndexStr = vertexStr.substr(0, pos);
						size_t pos2 = vertexStr.find_first_of('/', pos + 1);
						std::string texcoordIndexStr = vertexStr.substr(pos + 1, pos2 - pos - 1);
						std::string normalIndexStr = vertexStr.substr(pos2 + 1, vertexStr.length() - pos2 - 1);
		
						int tmpVertexIndex = atoi(positionIndexStr.c_str()) - 1;
						int tmpUVIndex = atoi(texcoordIndexStr.c_str()) - 1;
						int tmpNormalIndex = atoi(normalIndexStr.c_str()) - 1;
						int tmpColorIndex = 0;
						//trim the same vertice
						size_t curVetexIndex = mesh->GetGeo()->FindVertexDefineIndex(tmpVertexIndex, tmpNormalIndex, tmpUVIndex, tmpColorIndex);
						if (curVetexIndex == -1)
						{
							// 顶点索引
							curVetexIndex = mesh->GetGeo()->GetVertexFaceSize();
							Liar::LiarVertexDefine* find = new Liar::LiarVertexDefine(tmpVertexIndex, tmpNormalIndex, tmpUVIndex, tmpColorIndex);
							mesh->GetGeo()->GetVertexFaces()->push_back(find);
						}
						
						mesh->GetGeo()->GetIndices()->push_back(static_cast<unsigned int>(curVetexIndex));
					}
				}

			}
		}
		
		mesh->GetGeo()->GetRawData()->SetPos(positions);
		mesh->GetGeo()->GetRawData()->SetNorm(normals);
		mesh->GetGeo()->GetRawData()->SetTexCoord(texcoords);

		Liar::LiarMaterial* mat = new Liar::LiarMaterial();
		mesh->GetMatrials()->push_back(mat);

		Liar::LiarTexture* tex = new Liar::LiarTexture();
		tex->SetPath(base);
		mat->GetTextures()->push_back(tex);
		mesh->Upload();

		return mesh;
	}

	Liar::LiarTexContext* AssetsMgr::GetTexContext(const std::string& fileName)
	{
		return GetTexContext(fileName.data());
	}

	AssetsMgr* AssetsMgr::m_instance = nullptr;
}
