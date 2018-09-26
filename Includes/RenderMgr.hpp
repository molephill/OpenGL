//
//  RenderMgr.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef RenderMgr_hpp
#define RenderMgr_hpp

#include "Entity.h"
#include "Model.h"

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
		Liar::LiarShaderProgram* m_shader;
        
        Liar::Entity* m_rootNode;

		unsigned int m_VAO;
		unsigned int m_VBO;
		unsigned int m_EBO;

		Liar::LiarMesh* m_testMesh;
		Liar::Model* m_testModel;

		unsigned int VAO, VBO, EBO;
        
    public:
        Camera3D* GetMainCamera() { return m_camera; };
		Entity* GetRoot() { return m_rootNode; };
		
    };
}

#endif /* RenderMgr_hpp */
