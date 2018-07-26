//
//  RenderMgr.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef RenderMgr_hpp
#define RenderMgr_hpp

#include <LiarMesh.h>

namespace Liar
{
    class RenderMgr
    {
    public:
		RenderMgr();
        ~RenderMgr();
        
    public:

		void SetSize(unsigned int, unsigned int);
        void Render();

	private:
		float m_red;
		float m_green;
		float m_blue;
		Liar::Camera3D* m_camera;
		Liar::Shader* m_shader;

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;

		Liar::LiarMesh* m_testMesh;
		
    };
}

#endif /* RenderMgr_hpp */
