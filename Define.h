//
//  Define.h
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Define_h
#define Define_h

#include "iostream"

// buffsize
const static int DEFAULT_BUFF_SIZE = 512;

// 窗口大小
const unsigned int WINDOW_W = 800;
const unsigned int WINDOW_H = 600;

// 资源路径
#define BASE_PATH "/Users/maowei/Downloads/C++/OpenGL/";

// log设置
#define LOG_FILE_NAME "log.txt";
//#define WRITE_LOG_ENABLE 1;

// 渲染模式
//#define RENDER_MOD_LINE 1;

// shader类型
enum ShaderType
{
    TYPE_VERTEXT = 0,
    TYPE_FRAGMENT = 1,
    TYPE_PROGROM = 2,
};

#endif /* Define_h */
