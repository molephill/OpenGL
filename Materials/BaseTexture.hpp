//
//  BaseTexture.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef BaseTexture_hpp
#define BaseTexture_hpp

#include <stdio.h>

#include <string>

#include "TextureDataMgr.hpp"

class BaseTexture
{
public:
    virtual ~BaseTexture();
    
protected:
    unsigned int m_ID;
    
public:
    unsigned int GetID() { return m_ID; };
    
    virtual void Use(int index = GL_TEXTURE0);
    
protected:
    virtual void ParseData(TextureData* data);
    
    void Init(std::string, int rgb_mod = GL_RGB);
};


#endif /* BaseTexture_hpp */
