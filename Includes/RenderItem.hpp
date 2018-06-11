//
//  RenderItem.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/5/27.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef RenderItem_hpp
#define RenderItem_hpp

#include <stdio.h>

#include "Shader.hpp"
#include "TextureDataMgr.hpp"

#include "Texture2D.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Liar
{
    class RenderItem
    {
    public:
        ~RenderItem();
        
    private:
        unsigned int m_VBO;
        unsigned int m_VAO;
        unsigned int m_EBO;
        
        Shader* m_shader;
        BaseTexture* m_texture1;
        BaseTexture* m_texture2;
        
    private:
        void InitBase();
        
    public:
        void Init();
        void Draw();
    };
}

#endif /* RenderItem_hpp */
