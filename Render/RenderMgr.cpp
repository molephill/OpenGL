//
//  RenderMgr.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "RenderMgr.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

RenderMgr::~RenderMgr()
{
    delete m_render;
}

void RenderMgr::Init()
{
    m_render = new RenderItem();
    m_render->Init();
}

void RenderMgr::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    m_render->Draw();
    
#ifdef RENDER_MOD_LINE
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
#endif
    glDrawArrays(GL_TRIANGLES, 0, 6);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
