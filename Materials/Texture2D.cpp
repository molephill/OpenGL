//
//  Texture2D.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "Texture2D.hpp"

using namespace std::placeholders;

Texture2D::Texture2D(std::string path, int rgb_mod, int wrap_mod, int lev_mod)
{
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mod);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mod);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, lev_mod);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, lev_mod);
    
    Init(path, rgb_mod);
}

Texture2D::~Texture2D()
{
    
}

void Texture2D::ParseData(TextureData* data)
{
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB
                     , data->GetWidth(), data->GetHeight()
                     , 0, data->GetRgbMod(), GL_UNSIGNED_BYTE
                     , data->GetData());
        
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

void Texture2D::Use(int index)
{
    glActiveTexture(index);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}
