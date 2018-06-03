//
//  OpenGLWindow.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/19.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef OpenGLWindow_hpp
#define OpenGLWindow_hpp

#include <stdio.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Define.h"
#include "RenderMgr.hpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

class OpenGLWindow
{
public:
    int InitGLFW(uint w = WINDOW_W, uint h = WINDOW_H);
    
private:
    RenderMgr* m_renderMgr;
};

#endif /* OpenGLWindow_hpp */
