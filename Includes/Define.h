//
//  Define.h
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Define_h
#define Define_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include <string>

// buffsize
const static int DEFAULT_BUFF_SIZE = 512;

// 窗口大小
const unsigned int WINDOW_W = 800;
const unsigned int WINDOW_H = 600;

// 资源路径
#ifdef __APPLE__
const std::string BASE_PATH = "/Users/maowei/Downloads/C++/OpenGL/";
#else
const std::string BASE_PATH = "E:/c++/VSOpenGL/OpenGL/Assets/";
#endif

// log设置
#define LOG_FILE_NAME "log.txt";
//#define WRITE_LOG_ENABLE 1;

// 渲染模式
//#define RENDER_MOD_LINE 1;

// RENDER_DEBUG
//#define RENDER_DEBUG 1

// 相机默认参数
const float CAMERA_YAW		= -90.0f;
const float CAMERA_PITCH	= 0.0f;

const float CAMERA_FOV = 45.0f;

// shader类型
enum ShaderType
{
    TYPE_VERTEXT = 0,
    TYPE_FRAGMENT = 1,
    TYPE_PROGROM = 2,
};

// 移动方向
enum MOVE_DIRECTION
{
    FORWARD = 0,
    BACKWARD = 1,
    LEFT,
    RIGHT,
};

#endif /* Define_h */
