//
//  TextureDataMgr.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "TextureDataMgr.hpp"

namespace Liar
{
    TextureDataMgr::TextureDataMgr()
    {
        m_datas = new vector<TextureData*>();
    }
    
    TextureDataMgr::~TextureDataMgr()
    {
        for(vector<TextureData*>::iterator iter = m_datas->begin(); iter != m_datas->end(); iter++)
        {
            delete *iter;
        }
    }
    
    void TextureDataMgr::LoadTextureData(std::string& path, TDCallFun ParseData, int rgb_mod)
    {
        
        for(vector<TextureData*>::const_iterator citer = m_datas->begin(); citer != m_datas->end(); citer++)
        {
            if(path == (*citer)->GetPath())
            {
                ParseData(*citer);
                return;
            }
        }
        
        TextureData* data = new TextureData(path, rgb_mod);
        m_datas->push_back(data);
        ParseData(data);
    }
    
    TextureData* TextureDataMgr::GetTextureData(std::string& path) const
    {
        for(vector<TextureData*>::const_iterator citer = m_datas->begin(); citer != m_datas->end(); citer++)
        {
            if(path == (*citer)->GetPath())
            {
                return *citer;
            }
        }
        return nullptr;
    }
    
    void TextureDataMgr::ReleaseData(std::string& path)
    {
        for(vector<TextureData*>::iterator iter = m_datas->begin(); iter != m_datas->end(); iter++)
        {
            if((*iter)->GetPath() == path)
            {
                delete *iter;
                return;
            }
        }
    }
}
