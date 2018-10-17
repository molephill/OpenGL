#include "LiarShadowMap.h"
#include <AssetsMgr.hpp>

#include <glad/glad.h>

namespace Liar
{
	LiarBaseShadowMap::LiarBaseShadowMap():
		Liar::LiarDisplayObject(),
		m_width(Liar::WINDOW_W), m_height(Liar::WINDOW_H),
		m_lightPosition(new Liar::Vector3D()),
		m_lightDirection(new Liar::Vector3D()),
		m_lightTransformChanged(true),
		m_lightViewTransform(new Liar::Matrix4())
	{

	}

	LiarBaseShadowMap::~LiarBaseShadowMap()
	{
		delete m_lightPosition;
		delete m_lightDirection;
		delete m_lightViewTransform;
	}

	void LiarBaseShadowMap::SetLightPosition(float x, float y, float z)
	{
		if (!m_position->Equal(x, y, z))
		{
			m_position->Set(x, y, z);
			m_lightTransformChanged = true;
		}
	}

	void LiarBaseShadowMap::SetLightPosition(const Liar::Vector3D& pos)
	{
		SetLightPosition(pos.x, pos.y, pos.z);
	}

	void LiarBaseShadowMap::SetLightDirection(float x, float y, float z)
	{
		if (!m_lightDirection->Equal(x, y, z))
		{
			m_lightDirection->Set(x, y, z);
			m_lightTransformChanged = true;
		}
	}

	void LiarBaseShadowMap::SetLightDirection(const Liar::Vector3D& dir)
	{
		SetLightDirection(dir.x, dir.y, dir.z);
	}

	bool LiarBaseShadowMap::Render(const Liar::Camera3D& camera)
	{
		bool calcResult = Liar::LiarDisplayObject::CalcTransform(false, false);
		if (m_lightTransformChanged)
		{
			m_lightViewTransform->Identity();
			m_lightViewTransform->Translate(-m_position->x, -m_position->y, -m_position->z);
			m_lightViewTransform->LookAt(*m_lightDirection);
			m_lightTransformChanged = false;

			calcResult = true;
		}
		m_shaderProgram->Use();
		m_shaderProgram->SetMat4("projection", *(camera.GetProjMatrix()));
		m_shaderProgram->SetMat4("viewMatrix", *m_lightViewTransform);
		m_shaderProgram->SetMat4("viewExtentionMatrix", *(camera.GetExtentionMatrix()));
		m_shaderProgram->SetMat4("model", *(m_transform));

		return calcResult;
	}

	LiarShadowMap::LiarShadowMap():
		Liar::LiarBaseShadowMap(),
		m_mapCount(1),
		m_frameBuffer(0),m_shadowMaps(new std::vector<Liar::uint>())
	{
		Init();
	}


	LiarShadowMap::~LiarShadowMap()
	{
		if (m_frameBuffer > 0)
		{
			glDeleteFramebuffers(1, &m_frameBuffer);
		}
		ReleaseSub();
		delete m_shadowMaps;

		if (!Liar::AssetsMgr::GetInstance().ReleaseShaderProgram(m_shaderProgram))
		{
			delete m_shaderProgram;
			m_shaderProgram = nullptr;
		}
	}

	void LiarShadowMap::SetSize(Liar::uint w, Liar::uint h)
	{
		if (m_width != w || m_height != h)
		{
			m_width = w;
			m_height = h;

			ReleaseSub();
			CreateSub();
		}
	}

	void LiarShadowMap::Init()
	{
		m_shaderProgram = Liar::AssetsMgr::GetInstance().GetShaderProgrom("shadowMap",
			Liar::AssetsMgr::GetPath("Shaders/shadow_map.vs").c_str(), Liar::AssetsMgr::GetPath("Shaders/shadow_map.fs").c_str());

		// Create the FBO
		glGenFramebuffers(1, &m_frameBuffer);

		CreateSub();

		// Disable writes to the color buffer
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
	}

	void LiarShadowMap::CreateSub()
	{
		for (size_t i = 0; i < m_mapCount; ++i) 
		{
			GLuint tmpTexId = 0;
			glGenTextures(1, &tmpTexId);
			m_shadowMaps->push_back(tmpTexId);
			glBindTexture(GL_TEXTURE_2D, tmpTexId);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		BindForWriting();
	}

	void LiarShadowMap::ReleaseSub()
	{
		for (size_t i = 0; i < m_mapCount; ++i)
		{
			GLuint tmpTexId = m_shadowMaps->at(i);
			if (tmpTexId > 0)
			{
				glDeleteTextures(1, &tmpTexId);
			}
		}
	}

	void LiarShadowMap::BindForWriting(size_t cascadeIndex)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_shadowMaps->at(cascadeIndex), 0);
	}

	void LiarShadowMap::BindForReading()
	{
		for (size_t i = 0; i < m_mapCount; ++i)
		{
			GLenum texDefine = GL_TEXTURE1;
			switch (i)
			{
			case 1:
				texDefine = GL_TEXTURE6;
				break;
			case 2:
				texDefine = GL_TEXTURE7;
				break;
			default:
				texDefine = GL_TEXTURE1;
			}
			glActiveTexture(texDefine);
			glBindTexture(GL_TEXTURE_2D, m_shadowMaps->at(i));
		}
	}

	LiarCubeShadowMap::LiarCubeShadowMap() :
		m_width(Liar::WINDOW_W), m_height(Liar::WINDOW_H),
		m_frameBuffer(0), m_shadowMap(0), m_depth(0)
	{
		Init();
	}

	LiarCubeShadowMap::~LiarCubeShadowMap()
	{
		if (m_frameBuffer != 0) 
		{
			glDeleteFramebuffers(1, &m_frameBuffer);
		}

		if (m_shadowMap != 0) 
		{
			glDeleteTextures(1, &m_shadowMap);
		}

		if (m_depth != 0) 
		{
			glDeleteTextures(1, &m_depth);
		}
	}

	void LiarCubeShadowMap::Init()
	{
		// Create the FBO
		glGenFramebuffers(1, &m_frameBuffer);

		// Create the cube map
		glGenTextures(1, &m_shadowMap);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_shadowMap);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depth, 0);

		// Disable writes to the color buffer
		glDrawBuffer(GL_NONE);

		// Disable reads from the color buffer
		glReadBuffer(GL_NONE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void LiarCubeShadowMap::CreateSub()
	{
		// Create the depth buffer
		glGenTextures(1, &m_depth);
		glBindTexture(GL_TEXTURE_2D, m_depth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);

		for (uint i = 0; i < 6; i++) 
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_R32F, m_width, m_height, 0, GL_RED, GL_FLOAT, NULL);
		}
	}

	void LiarCubeShadowMap::ReleaseSub()
	{
		if (m_depth != 0)
		{
			glDeleteTextures(1, &m_depth);
		}
	}

	void LiarCubeShadowMap::BindForWriting(GLenum cubeFace)
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_frameBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, cubeFace, m_shadowMap, 0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}

	void LiarCubeShadowMap::BindForReading(GLenum texUint)
	{
		glActiveTexture(texUint);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_shadowMap);
	}
}
