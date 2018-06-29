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
#include "Light.hpp"
#include "LiarPrefab.hpp"

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
		DirectLight* GetMainLight() { return m_mainLight; };

		void SetSize(unsigned int, unsigned int);
        void Render();


	private:
		Camera* m_camera;
        DirectLight* m_mainLight;
        
    private:
        RenderItem* m_render;
        Cube* m_cube;
    };
}

#endif /* RenderMgr_hpp */
