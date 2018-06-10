//
//  TextureDataMgr.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef TextureDataMgr_hpp
#define TextureDataMgr_hpp

#include <stdio.h>

#include <string>
#include <vector>

#include "TextureData.hpp"

using namespace std;

// 定义回调函数
typedef std::function<void(TextureData*)> TDCallFun;

class TextureDataMgr
{
public:
    static TextureDataMgr& GetInstance()
    {
        static TextureDataMgr m_instance;
        return m_instance;
    }
    
private:
    TextureDataMgr();
    ~TextureDataMgr();
    
private:
    std::vector<TextureData*>* m_datas;
    
public:
    void LoadTextureData(string&, TDCallFun, int rgb_mod = GL_RGB);
    void ReleaseData(string&);
    TextureData* GetTextureData(string&) const;
};

#endif /* TextureDataMgr_hpp */
