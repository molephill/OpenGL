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
        m_textureDatas = new vector<LiarTextureData*>();
    }
    
    AssetsMgr::~AssetsMgr()
    {
        for(vector<LiarTextureData*>::iterator iter = m_textureDatas->begin(); iter != m_textureDatas->end(); iter++)
        {
            delete *iter;
        }
    }
    
    LiarTextureData* AssetsMgr::GetTextureData(std::string& path, int rgbMod)
    {
        for(vector<LiarTextureData*>::const_iterator citer = m_textureDatas->begin(); citer != m_textureDatas->end(); citer++)
        {
            if((*citer)->CheckSamePath(path))
            {
                (*citer)->IncRefCount();
                return *citer;
            }
        }
        
        LiarTextureData* data = new LiarTextureData(path, rgbMod);
        m_textureDatas->push_back(data);
        
        return data;
    }
    
    void AssetsMgr::ReleaseTextureData(const std::string& path)
    {
        for(vector<LiarTextureData*>::iterator iter = m_textureDatas->begin(); iter != m_textureDatas->end();)
        {
			if ((*iter)->CheckSamePath(path))
            {
                int refCount = (*iter)->DecRefCount();
                if(refCount <= 0)
                {
                    delete *iter;
                    iter = m_textureDatas->erase(iter);
                }
                else
                {
                    ++iter;
                }
            }
            else
            {
                ++iter;
            }
        }
    }
    
    void AssetsMgr::ReleaseTextureData(Liar::LiarTextureData* check)
    {
        if(!check) return;
        
        for(vector<LiarTextureData*>::iterator iter = m_textureDatas->begin(); iter != m_textureDatas->end();)
        {
            if ((*iter) == check)
            {
                int refCount = (*iter)->DecRefCount();
                if(refCount <= 0)
                {
                    delete *iter;
                    iter = m_textureDatas->erase(iter);
                }
                else
                {
                    ++iter;
                }
            }
            else
            {
                ++iter;
            }
        }
    }

	AssetsMgr* AssetsMgr::m_instance = nullptr;
}
