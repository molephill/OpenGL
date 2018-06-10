//
//  Texture2D.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp

#include <stdio.h>

#include <string>

#include "BaseTexture.hpp"

class Texture2D
    :public BaseTexture
{
public:
    Texture2D(std::string, int rgb_mod = GL_RGB, int wrap_mod = GL_REPEAT, int lev_mod = GL_LINEAR);
    ~Texture2D();
    
protected:
    virtual void ParseData(TextureData* data);
    
public:
    virtual void Use(int index = GL_TEXTURE0);
};

#endif /* Texture2D_hpp */
