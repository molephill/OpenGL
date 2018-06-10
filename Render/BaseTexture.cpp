//
//  BaseTexture.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "BaseTexture.hpp"

//BaseTexture::~BaseTexture()
//{
////    glDeleteTextures(1, m_texture);
//}

BaseTexture::BaseTexture(std::string path):m_width(0),m_height(0),m_nrChannels(0)
{
    m_path = path;
    
    // load and create a texture
    // -------------------------
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // cache
    Load();
}

bool BaseTexture::Load()
{
    unsigned char* data = stbi_load(m_path.c_str(), &m_width, &m_height, &m_nrChannels, 0);
    
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        return true;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        return false;
    }
}

void BaseTexture::Use()
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
