//
//  TextureData.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef TextureData_hpp
#define TextureData_hpp

#include <stdio.h>
#include <string>

#include <glad/glad.h>

#include <iostream>

#include <stb_image.h>

class TextureData
{
public:
    TextureData(std::string&, int rgb_mod = GL_RGB);
    ~TextureData();
    
private:
    std::string m_path;
    
    int m_width;
    int m_height;
    int m_nrChannels;
    
    int m_rgb_mod;
    
    unsigned char* m_data;
    
public:
    int GetWidth() const {return m_width;};
    int GetHeight() const {return m_height;};
    int GetNrChannels() const {return m_nrChannels;};
    int GetRgbMod() const {return m_rgb_mod;};
    std::string GetPath() const {return m_path;};
    unsigned char* GetData() const {return m_data;};
    
private:
    bool Load();
};

#endif /* TextureData_hpp */
