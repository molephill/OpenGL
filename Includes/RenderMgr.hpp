//
//  RenderMgr.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef RenderMgr_hpp
#define RenderMgr_hpp

#include "Model.h"
#include "LightsMgr.h"

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
        
        Liar::LiarContainerObject* m_rootNode;
		Liar::LightsMgr* m_lightsMgr;

		

	private:
		Liar::LiarMesh* m_testMesh;
		Liar::Model* m_testModel;

		unsigned int VAO, VBO, EBO, cubeVAO;
		unsigned int diffuseMap;
		unsigned int specularMap;
        
    public:
        Camera3D* GetMainCamera() { return m_camera; };
		LiarContainerObject* GetRoot() { return m_rootNode; };

	private:
		void InitTest();
		void RenderTest();
		void BuildTest();
    };
}

#endif /* RenderMgr_hpp */
