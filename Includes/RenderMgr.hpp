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
#include "Camera.hpp"

namespace Liar
{
    class RenderMgr
    {
    public:
		RenderMgr();
        ~RenderMgr();
        
    public:
		void Init();

		Camera* GetCamera() { return m_camera; };

		void SetSize(unsigned int, unsigned int);
        void Render();


	private:
		Camera* m_camera;
        
    private:
        RenderItem* m_render;
    };
}

#endif /* RenderMgr_hpp */
