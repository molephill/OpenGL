//
//  Texture.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/23.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include "LiarAssetsData.hpp"
#include "AssetsMgr.hpp"

namespace Liar
{
    class Texture2D
        :public LiarBaseAssetsData
    {
    public:
        Texture2D(std::string, int rgb_mod = GL_RGB, int wrap_mod = GL_REPEAT, int lev_mod = GL_LINEAR);
        ~Texture2D();
        
    protected:
        unsigned int m_id;
        int m_wrapMod;
        int m_levMod;
        LiarTextureData* m_data;
        
    public:
        bool Upload();
        
    public:
        virtual void Use(int index = GL_TEXTURE0);
    };
    
    class DiffuseMap:public Texture2D
    {
        
    };
    
    class SpecularMap:public Texture2D
    {
        
    };
    
    class Material:public Texture2D
    {
        
    };
}

#endif /* Texture_hpp */
