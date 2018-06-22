//
//  LiarPrefab.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/17.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef LiarPrefab_hpp
#define LiarPrefab_hpp

#include <stdio.h>
#include "LiarObject.hpp"

#include "Shader.hpp"
#include "AssetsMgr.hpp"
#include "Texture.hpp"

namespace Liar
{
    class Cube:public LiarObject
    {
    public:
        Cube();
    protected:
        virtual void Upload();
        
    private:
        Texture2D* m_texture1;
        Texture2D* m_texture2;
        
    public:
        virtual void Render(Liar::RenderMgr*, bool calcInvest = true);
    };
}

#endif /* LiarPrefab_hpp */
