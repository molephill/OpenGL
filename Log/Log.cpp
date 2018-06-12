//
//  Log.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/20.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "Log.hpp"

void CLog::GetLogFilePath(char* szPath)
{
//    GetModuleFileNameA( NULL, szPath, PATH_MAX) ;
//    ZeroMemory(strrchr(szPath,_T('\\')), strlen(strrchr(szPath,_T('\\') ) )*sizeof(char)) ;
//    strcat(szPath,"\\");
//    strcat(szPath, LOG_FILE_NAME);
}

string CLog::GetSystemTime()
{
#ifndef __APPLE__
	time_t tNowTime = time(0);
	tm* tLocalTime = nullptr;
	localtime_s(tLocalTime, &tNowTime);
#else
	time_t tNowTime;
	time(&tNowTime);
	tm* tLocalTime = localtime(&tNowTime);
#endif // WIN_PLAT_FORM
    char szTime[30] = {'\0'};
    strftime(szTime, 30, "[%Y-%m-%d %H:%M:%S] ", tLocalTime);
    string strTime = szTime;
    return strTime;
}

//输出一个内容，可以是字符串(ascii)、整数、浮点数、布尔、枚举
//格式为：[2011-11-11 11:11:11] aaaaaaa并换行
template <typename T>
void CLog::WriteLog(T x)
{
#ifdef WRITE_LOG_ENABLE
    char szPath[PATH_MAX] = {0};
    GetLogFilePath(szPath);
    ofstream fout(szPath,ios::app);
    fout.seekp(ios::end);
    fout << GetSystemTime() << x <<endl;
    fout.close();
#elseif DEBUG
    std::cout << GetSystemTime() << x << std::endl;
#endif
}

//输出2个内容，以等号连接。一般用于前面是一个变量的描述字符串，后面接这个变量的值
template<typename T1,typename T2>
void CLog::WriteLog2(T1 x1,T2 x2)
{
#ifdef WRITE_LOG_ENABLE
    char szPath[PATH_MAX] = {0};
    GetLogFilePath(szPath);
    ofstream fout(szPath,ios::app);
    fout.seekp(ios::end);
    fout << GetSystemTime() << x1 <<" = "<< x2 << endl;
    fout.close();
#elseif DEBUG
    std::cout << GetSystemTime() << x1 << "=" << x2 << std::endl;
#endif
}

//输出一行当前函数开始的标志,宏传入__FUNCTION__
template <typename T>
void CLog::WriteFuncBegin(T x)
{
#ifdef WRITE_LOG_ENABLE
    char szPath[PATH_MAX] = {0};
    GetLogFilePath(szPath);
    ofstream fout(szPath,ios::app);
    fout.seekp(ios::end);
    fout << GetSystemTime() << "--------------------"<< x <<"  Begin  --------------------" << std::endl;
    fout.close();
#elseif DEBUG
    std::cout << GetSystemTime() << "--------------------"<< x <<"  Begin  --------------------" << std::endl;
#endif
}

//输出一行当前函数结束的标志，宏传入__FUNCTION__
template <typename T>
void CLog::WriteFuncEnd(T x)
{
#ifdef WRITE_LOG_ENABLE
    char szPath[PATH_MAX] = {0};
    GetLogFilePath(szPath);
    ofstream fout(szPath,ios::app);
    fout.seekp(ios::end);
    fout << GetSystemTime() << "--------------------"<< x <<"  End  --------------------" << endl;
    fout.close();
#elseif DEBUG
    std::cout << GetSystemTime() << "--------------------"<< x <<"  End  --------------------" << std::endl;
#endif
}
