//
//  TextureData.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "TextureData.hpp"

namespace Liar
{
    TextureData::TextureData(std::string& path, int rgb_type):m_rgb_mod(rgb_type), m_refCount(1)
    {
        m_path = path;
        Load();
    }
    
    TextureData::~TextureData()
    {
        stbi_image_free(m_data);
    }
    
    bool TextureData::Load()
    {
        m_data = stbi_load(m_path.c_str(), &m_width, &m_height, &m_nrChannels, 0);
        if(m_data)
        {
            return true;
        }
        else
        {
            std::cout << "Failed to load texture" << m_path << std::endl;
            return false;
        }
    }
}
