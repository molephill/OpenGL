//
//  LiarObject.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/16.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef LiarObject_hpp
#define LiarObject_hpp

#include <stdio.h>
#include "Define.h"
#include "Component.hpp"
#include "Global.hpp"
#include "Shader.hpp"
#include "LiarUtil.hpp"

namespace Liar
{
    class RenderMgr;
    
    class LiarObject
    {
    public:
        LiarObject();
        LiarObject(float, float, float);
        virtual ~LiarObject();
        
    protected:
        
        unsigned int m_vbo;
        unsigned int m_vao;
        
        Shader* m_shader;
        
        CPosition* m_position;
        CRotation* m_rotation;
        CScale* m_scale;
        bool m_isDirty;
        
        glm::mat4 m_matrix;
        
    public:
        // ===================================================
        virtual void SetPosition(const glm::vec3&);
        virtual void SetPosition(float, float, float);
        // ===================================================
        virtual void AddPosition(const glm::vec3&);
        virtual void AddPosition(float, float, float);
        // ===================================================
        virtual void SetRotation(const glm::vec3&);
        virtual void SetRotation(float, float, float);
        // ===================================================
        virtual void AddRotation(const glm::vec3&);
        virtual void AddRotation(float, float, float);
        // ===================================================
        virtual void SetScale(const glm::vec3&);
		virtual void SetScale(float);
        virtual void SetScale(float, float, float);
        // ===================================================
        virtual void AddScale(const glm::vec3&);
        virtual void AddScale(float, float, float);
        
        virtual void Render(Liar::RenderMgr*);
        
    protected:
        virtual void Upload();
        
    public:
        // ===================================================
        unsigned int GetVBO() { return m_vbo; };
        
        glm::vec3& GetPosition() { return m_position->GetValue(); };
        glm::vec3& GetRotation() { return m_rotation->GetValue(); };
        glm::vec3& GetScale() { return m_scale->GetValue(); };
        
        float GetX() const { return m_position->GetX(); };
        float GetY() const { return m_position->GetY(); };
        float GetZ() { return m_position->GetZ(); };
        
        float GetRX() const { return m_rotation->GetX(); };
        float GetRY() const { return m_rotation->GetY(); };
        float GetRZ() const { return m_rotation->GetZ(); };
        
        float GetSX() const { return m_scale->GetX(); };
        float GetSY() const { return m_scale->GetY(); };
        float GetSZ() const { return m_scale->GetZ(); };
    };
}

#endif /* LiarObject_hpp */
