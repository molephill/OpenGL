//
//  Log.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Log_hpp
#define Log_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#ifdef WRITE_LOG_ENABLE
#include <fstream>
#endif

#include <string>
#include <ctime>

#ifndef __APPLE__
#include <time.h>
#endif // !__APPLE__


#include "Define.h"

using namespace std;

class CLog
{
public:
    static void GetLogFilePath(char* szPath);
    
    //输出一个内容，可以是字符串(ascii)、整数、浮点数、布尔、枚举
    //格式为：[2011-11-11 11:11:11] aaaaaaa并换行
    template <typename T>
    static void WriteLog(T x);
    
    //输出2个内容，以等号连接。一般用于前面是一个变量的描述字符串，后面接这个变量的值
    template<typename T1,typename T2>
    static void WriteLog2(T1 x1,T2 x2);
    
    //输出一行当前函数开始的标志,宏传入__FUNCTION__
    template <typename T>
    static void WriteFuncBegin(T x);
    
    //输出一行当前函数结束的标志，宏传入__FUNCTION__
    template <typename T>
    static void WriteFuncEnd(T x);
    
    //获取本地时间，格式如"[2011-11-11 11:11:11] ";
    static string GetSystemTime();
};

#define LOG(x)  CLog::WriteLog(x);  //括号内可以是字符串(ascii)、整数、浮点数、bool等
#define LOG2(x1,x2)     CLog::WriteLog2(x1,x2);
#define LOG_FUNC        LOG(__FUNCTION__)               //输出当前所在函数名
#define LOG_LINE        LOG(__LINE__)                       //输出当前行号
#define LOG_FUNC_BEGIN  CLog::WriteFuncBegin(__FUNCTION__);     //形式如：[时间]"------------FuncName Begin------------"
#define LOG_FUNC_END     CLog::WriteFuncEnd(__FUNCTION__);      //形式如：[时间]"------------FuncName  End------------"


#endif /* Log_hpp */
