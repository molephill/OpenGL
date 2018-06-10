//
//  BaseTexture.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/10.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef BaseTexture_hpp
#define BaseTexture_hpp

#include <stdio.h>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

class BaseTexture
{
public:
    BaseTexture(std::string);
//    ~BaseTexture();
    
private:
    bool Load();
    
public:
    void Use();
    
    int GetWidth() const {return m_width;};
    int GetHeight() const {return m_height;};
    
    unsigned int GetTexture() const {return m_texture;};
    
private:
    std::string m_path;
    
    int m_width;
    int m_height;
    int m_nrChannels;
    
    unsigned int m_texture;
};

#endif /* BaseTexture_hpp */
