//
//  AssetsMgr.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#include <AssetsMgr.hpp>

namespace Liar
{
	AssetsMgr::AssetsMgr() :
		m_mapTextures(new std::map<const char*, Liar::LiarTexture*>()),
		m_mapGeometeries(new std::map<const char*, Liar::LiarGeometry*>()),
		m_mapShaderCodes(new std::map<const char*, std::string>()),
		m_mapShaderPrograms(new std::map<const char*, Liar::LiarShaderProgram*>()),
		m_allSkeletons(new std::vector<Liar::LiarSkeleton*>())
	{
	}

	AssetsMgr::~AssetsMgr()
	{
	}

	Liar::LiarGeometry* AssetsMgr::GetGeometryData(const char* fileName)
	{
		std::map<const char*, Liar::LiarGeometry*>::iterator iter = m_mapGeometeries->find(fileName);;

		if (iter != m_mapGeometeries->end())
		{
			iter->second->IncRefCount();
			return iter->second;
		}
		else
		{
			Liar::LiarMeshRawData* rawData = Liar::LiarPluginRead::ReadMeshRawData(fileName);
			Liar::LiarGeometry* geo = new Liar::LiarGeometry();
			geo->SetRawData(rawData);
			m_mapGeometeries->insert(std::pair<const char*, Liar::LiarGeometry*>(fileName, geo));
			return geo;
		}
	}

	bool AssetsMgr::ReleaseGeometryData(Liar::LiarGeometry* rawData)
	{
		if (rawData)
		{
			std::map<const char*, Liar::LiarGeometry*>::iterator iter = m_mapGeometeries->begin();
			while (iter != m_mapGeometeries->end())
			{
				if (iter->second == rawData)
				{
					if (rawData->DesRefCount() <= 0)
					{
						delete rawData;
						m_mapGeometeries->erase(iter->first);
					}
					return true;
				}
				iter++;
			}
		}

		return false;
	}

	Liar::LiarTexture* AssetsMgr::GetTexture(const char* fileName)
	{
		std::map<const char*, Liar::LiarTexture*>::iterator iter = m_mapTextures->find(fileName);;

		if (iter != m_mapTextures->end())
		{
			iter->second->IncRefCount();
			return iter->second;
		}
		else
		{
			Liar::LiarTexture* tex = new Liar::LiarTexture();
			tex->Upload(fileName);
			m_mapTextures->insert(std::pair<const char*, Liar::LiarTexture*>(fileName, tex));
			return tex;
		}
	}

	bool AssetsMgr::ReleaseTexture(Liar::LiarTexture* tex)
	{
		if (!tex) return false;
		std::map<const char*, Liar::LiarTexture*>::iterator iter = m_mapTextures->begin();
		while (iter != m_mapTextures->end())
		{
			if (iter->second == tex)
			{
				if (tex->DesRefCount() <= 0)
				{
					delete tex;
					m_mapTextures->erase(iter->first);
				}
				return true;
			}
			iter++;
		}
		return false;
	}

	std::string AssetsMgr::GetBaseShaderCode(const char* fileName) const
	{
		std::map<const char*, std::string>::iterator iter = m_mapShaderCodes->find(fileName);

		if (iter != m_mapShaderCodes->end())
		{
			return (iter->second);
		}
		else
		{
			Liar::LiarBaseShader* shader = new Liar::LiarBaseShader();
			std::string code = shader->Load(fileName);
			delete shader;
			m_mapShaderCodes->insert(std::pair<const char*, std::string>(fileName, code));
			return code;
		}
	}

	Liar::LiarShaderProgram* AssetsMgr::GetShaderProgrom(const char* name, const char* vertexFile, const char* fragmentFile)
	{
		std::map<const char*, Liar::LiarShaderProgram*>::iterator iter = m_mapShaderPrograms->find(name);
		if (iter != m_mapShaderPrograms->end())
		{
			iter->second->IncRefCount();
			return iter->second;
		}
		else
		{
			Liar::LiarShaderProgram* program = new Liar::LiarShaderProgram();
			program->Load(vertexFile, fragmentFile);
			m_mapShaderPrograms->insert(std::pair<const char*, Liar::LiarShaderProgram*>(name, program));
			return program;
		}
	}

	bool AssetsMgr::ReleaseShaderProgram(Liar::LiarShaderProgram* program)
	{
		if (!program) return false;
		std::map<const char*, Liar::LiarShaderProgram*>::iterator iter = m_mapShaderPrograms->begin();
		while (iter != m_mapShaderPrograms->end())
		{
			if (iter->second == program)
			{
				if (program->DesRefCount() <= 0)
				{
					delete program;
					m_mapShaderPrograms->erase(iter->first);
				}
				return true;
			}
			iter++;
		}
		return false;
	}


	/*Liar::LiarSkeleton* AssetsMgr::GetSkeleton(const char* path)
	{
		if (!path) return nullptr;
		Liar::LiarSkeleton* ret = nullptr;
		for (std::vector<Liar::LiarSkeleton*>::iterator it = m_allSkeletons->begin(); it < m_allSkeletons->end();)
		{
			if (std::strcmp(path, (*it)->GetPath().data()) == 0)
			{
				ret = *it;
				break;
			}
		}

		if (!ret)
		{
			ret = Liar::LiarPluginRead::ReadSkeleton(path);
			ret->SetPath(path);
			m_allSkeletons->push_back(ret);
		}
		ret->IncRefCount();
		return ret;
	}

	Liar::LiarSkeleton* AssetsMgr::GetSkeleton(const std::string& path)
	{
		return GetSkeleton(path.c_str());
	}*/

	std::string AssetsMgr::GetPath(const char* base)
	{
		return "" + BASE_PATH + base;
	}

	//void AssetsMgr::PrintMat4(const glm::mat4 & view)
	//{
	//	std::cout << std::fixed << std::setprecision(5);
	//	std::cout << "[" << std::setw(10) << view[0][0] << " " << std::setw(10) << view[0][1] << " " << std::setw(10) << view[0][2] << " " << std::setw(10) << view[0][3] << "]\n"
	//		<< "[" << std::setw(10) << view[1][0] << " " << std::setw(10) << view[1][1] << " " << std::setw(10) << view[1][2] << " " << std::setw(10) << view[1][3] << "]\n"
	//		<< "[" << std::setw(10) << view[2][0] << " " << std::setw(10) << view[2][1] << " " << std::setw(10) << view[2][2] << " " << std::setw(10) << view[2][3] << "]\n"
	//		<< "[" << std::setw(10) << view[3][0] << " " << std::setw(10) << view[3][1] << " " << std::setw(10) << view[3][2] << " " << std::setw(10) << view[3][3] << "]\n";
	//	std::cout << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	//}

	AssetsMgr* AssetsMgr::m_instance = nullptr;
}