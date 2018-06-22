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
    AssetsMgr::AssetsMgr()
    {
        m_textureDatas = new vector<TextureData*>();
    }
    
    AssetsMgr::~AssetsMgr()
    {
        for(vector<TextureData*>::iterator iter = m_textureDatas->begin(); iter != m_textureDatas->end(); iter++)
        {
            delete *iter;
        }
    }
    
    void AssetsMgr::LoadTextureData(std::string& path, TDCallFun ParseData, int rgb_mod)
    {
        
        for(vector<TextureData*>::const_iterator citer = m_textureDatas->begin(); citer != m_textureDatas->end(); citer++)
        {
            if((*citer)->CheckSamePath(path))
            {
                ParseData(*citer);
                return;
            }
        }
        
        TextureData* data = new TextureData(path, rgb_mod);
        m_textureDatas->push_back(data);
        ParseData(data);
    }
    
    TextureData* AssetsMgr::GetTextureData(std::string& path) const
    {
        for(vector<TextureData*>::const_iterator citer = m_textureDatas->begin(); citer != m_textureDatas->end(); citer++)
        {
            if((*citer)->CheckSamePath(path))
            {
                return *citer;
            }
        }
        return nullptr;
    }
    
    void AssetsMgr::ReleaseData(std::string& path)
    {
        for(vector<TextureData*>::iterator iter = m_textureDatas->begin(); iter != m_textureDatas->end(); iter++)
        {
			if ((*iter)->CheckSamePath(path))
            {
				int refCount = (*iter)->Release();
				if ( refCount <= 0)
				{
					m_textureDatas->erase(iter);
				}
            }
        }
    }

	AssetsMgr* AssetsMgr::m_instance = nullptr;
}
