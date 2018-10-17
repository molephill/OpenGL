//
//  RenderMgr.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef RenderMgr_hpp
#define RenderMgr_hpp

#include "LightsMgr.h"
#include "ILiarRender.h"

namespace Liar
{
    class RenderMgr:public ILiarRenderParameter
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
		Liar::LiarShaderProgram* m_renderShader;
        
        Liar::LiarContainerObject* m_rootNode;
		Liar::LightsMgr* m_lightsMgr;

		Liar::LiarBaseShadowMap* m_shadowMap;

	public:
		LiarContainerObject* GetRoot() { return m_rootNode; };

		virtual Liar::Camera3D* GetMainCamera() { return m_camera; };
		virtual Liar::LiarShaderProgram* GetRenderShaderProgram() { return m_renderShader ? m_renderShader : m_shader; };
		virtual Liar::LiarBaseShadowMap* GetShadowMap() { return m_shadowMap; };
		virtual void SetRenderShaderProgram(Liar::LiarShaderProgram* v) { m_renderShader = v; };
    };
}

#endif /* RenderMgr_hpp */
