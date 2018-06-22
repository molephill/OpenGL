
//
//  TextureData.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef LiarAssetsData_hpp
#define LiarAssetsData_hpp

#include <string>
#include <iostream>
#include <stb_image.h>

#include "Define.h"

namespace Liar
{
    // ============== reference_data ================
    class LiarBaseAssetsData
    {
    public:
        LiarBaseAssetsData();
        ~LiarBaseAssetsData();
        
    protected:
        int m_refCount;
        
    public:
        void IncRefCount() { ++m_refCount; };
        int DecRefCount() { return --m_refCount; };
    };
    
    // ==============   texture_data ================
    class LiarTextureData:public LiarBaseAssetsData
    {
    public:
        LiarTextureData(std::string&, int);
        ~LiarTextureData();
        
    private:
        std::string m_path;
        int m_width;
        int m_height;
        int m_nrChannels;
        int m_rgb_mod;
        unsigned char* m_data;
        
    public:
        int GetWidth() const { return m_width; };
        int GetHeight() const { return m_height; };
        int GetNrChannels() const { return m_nrChannels; };
        int GetRgbMod() const { return m_rgb_mod; };
        unsigned char* GetData() const { return m_data; };
        bool CheckSamePath(const std::string& val) { return val == m_path; };
    };
}

#endif /* LiarAssetsData_hpp */

