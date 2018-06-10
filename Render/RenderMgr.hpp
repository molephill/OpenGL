//
//  RenderMgr.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef RenderMgr_hpp
#define RenderMgr_hpp

#include <stdio.h>

#include "RenderItem.hpp"

namespace Liar
{
    class RenderMgr
    {
    public:
        ~RenderMgr();
        
    public:
        void Init();
        void Render();
        
    private:
        RenderItem* m_render;
    };
}

#endif /* RenderMgr_hpp */
