//
//  BaseTexture.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "BaseTexture.hpp"

using namespace std::placeholders;

namespace Liar
{
    
    BaseTexture::~BaseTexture()
    {
        
    }
    
    void BaseTexture::Init(std::string path, int rgb_mod)
    {
        TDCallFun fun = std::bind(&BaseTexture::ParseData, this, _1);
        TextureDataMgr::GetInstance().LoadTextureData(path, fun, rgb_mod);
    }
    
    void BaseTexture::ParseData(TextureData *data)
    {
        
    }
    
    void BaseTexture::Use(int index)
    {
        
    }
}
