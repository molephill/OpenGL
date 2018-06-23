//
//  Texture.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/23.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include "LiarAssetsData.hpp"
#include "AssetsMgr.hpp"
#include "Shader.hpp"

namespace Liar
{
    class Texture2D
        :public LiarBaseAssetsData
    {
    public:
        Texture2D(std::string, int rgb_mod = GL_RGB, int wrap_mod = GL_REPEAT, int lev_mod = GL_LINEAR);
        ~Texture2D();
        
    protected:
        unsigned int m_id;
        int m_wrapMod;
        int m_levMod;
		float m_shininess;
        LiarTextureData* m_data;
        
    public:
		void ChangeWrapMod(int);
		void ChangeLevMod(int);
		void ChangeShininess(int);
        bool Upload();
        
    public:
        virtual void Use(Shader*, int index = GL_TEXTURE0);
    };

	class LiarMaterial :public Texture2D
	{
	public:
		LiarMaterial(std::string, int rgbMod = GL_RGB);
		LiarMaterial(std::string, const glm::vec3&, const glm::vec3&, int rgbMod = GL_RGB);

	protected:
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;

	public:
		void ChangeDiffuse(const glm::vec3&);
		void ChangeDiffuse(float, float, float);
		void ChangeSpecular(const glm::vec3&);
		void ChangeSpecular(float, float, float);
		virtual void Use(Shader*, int index = GL_TEXTURE0);
	};

}

#endif /* Texture_hpp */
