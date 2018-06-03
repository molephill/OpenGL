//
//  OpenGLWindow.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/19.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "OpenGLWindow.hpp"
#include "Log.hpp"

int OpenGLWindow::InitGLFW(uint w, uint h)
{
    if (!glfwInit()) {
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
    
    GLFWwindow* window = glfwCreateWindow(w, h, "OpenGL", NULL, NULL);
    
    if (!window) {
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
#ifdef DEBUG
//    cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << endl;
//    cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << endl;
//    cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
//    cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
#endif
    
    m_renderMgr = new RenderMgr();
    m_renderMgr->Init();
    
    while (!glfwWindowShouldClose(window)) {
        
        // -- input --
        processInput(window);
        
        // -- render --
        m_renderMgr->Render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    delete m_renderMgr;
    
    glfwTerminate();
    
    return 0;
}

// 响应窗口事件
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// 修改屏幕大小时
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
