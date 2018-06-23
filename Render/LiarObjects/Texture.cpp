//
//  Texture.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/23.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "Texture.hpp"

namespace Liar
{
    Texture2D::Texture2D(std::string path, int rgb_mod, int wrap_mod, int lev_mod):
    m_id(0),m_wrapMod(wrap_mod),m_levMod(lev_mod),m_shininess(32.0f)
    ,m_data(AssetsMgr::GetInstance().GetTextureData(path, rgb_mod))
    {
        
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mod);    // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mod);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, lev_mod);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, lev_mod);
        
        Upload();
    }
    
    Texture2D::~Texture2D()
    {
        AssetsMgr::GetInstance().ReleaseTextureData(m_data);
    }
    
    bool Texture2D::Upload()
    {
        if(m_data->GetData())
        {
            glGenTextures(1, &m_id);
            glBindTexture(GL_TEXTURE_2D, m_id); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
            
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB
                         , m_data->GetWidth(), m_data->GetHeight()
                         , 0, m_data->GetRgbMod(), GL_UNSIGNED_BYTE
                         , m_data->GetData());
            
            glGenerateMipmap(GL_TEXTURE_2D);
            
            return true;
        }
        else
        {
            return false;
        }
    }

	void Texture2D::ChangeLevMod(int mod)
	{
		if (m_levMod != mod)
		{
			m_levMod = mod;
		}
	}

	void Texture2D::ChangeWrapMod(int mod)
	{
		if (m_wrapMod != mod)
		{
			m_wrapMod = mod;
		}
	}

	void Texture2D::ChangeShininess(int v)
	{
		if (m_shininess != v)
		{
			m_shininess = v;
		}
	}
    
    void Texture2D::Use(Shader* shader, int index)
    {
        glActiveTexture(index);
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

	// ================================== Material ==================================
	LiarMaterial::LiarMaterial(std::string path, int rgbMod) 
		:Texture2D(path, rgbMod)
		,m_diffuse(glm::vec3(0.2)),m_specular(glm::vec3(0.5))
	{

	}

	LiarMaterial::LiarMaterial(std::string path, const glm::vec3& diffuse, const glm::vec3& specular, int rgbMod)
		:Texture2D(path, rgbMod)
		, m_diffuse(diffuse), m_specular(specular)
	{

	}

	void LiarMaterial::Use(Shader* shader, int index)
	{
		/*shader->SetVec3("material.specular", m_specular);
		shader->SetVec3("material.diffuse", m_diffuse);*/
		Texture2D::Use(shader, index);
	}

	void LiarMaterial::ChangeDiffuse(const glm::vec3& v)
	{
		if (m_diffuse != v)
		{
			m_diffuse = v;
		}
	}

	void LiarMaterial::ChangeDiffuse(float r, float g, float b)
	{
		if (m_diffuse.r != r || m_diffuse.g != g || m_diffuse.b != b)
		{
			m_diffuse.r = r;
			m_diffuse.b = b;
			m_diffuse.g = g;
		}
	}

	void LiarMaterial::ChangeSpecular(const glm::vec3& v)
	{
		if (m_diffuse != v)
		{
			m_diffuse = v;
		}
	}

	void LiarMaterial::ChangeSpecular(float r, float g, float b)
	{
		if (m_specular.r != r || m_specular.g != g || m_specular.b != b)
		{
			m_specular.r = r;
			m_specular.g = b;
			m_specular.b = b;
		}
	}

}
