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
using namespace Liar;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

namespace Liar
{
    class OpenGLWindow
    {
    public:
        int InitGLFW(unsigned int w = WINDOW_W, unsigned int h = WINDOW_H);
        
    public:
        static RenderMgr* renderMgr;
    };
}

#endif /* OpenGLWindow_hpp */
