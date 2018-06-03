//
//  main.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/19.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "OpenGLWindow.hpp"

int main() {

    OpenGLWindow* window = new OpenGLWindow();

    if(window->InitGLFW() < 0)
    {
        delete window;
    }
}
