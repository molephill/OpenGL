#pragma once

#include <string>
#include <vector>

#include <LiarVertexBuffer.h>
#include <LiarStringUtil.h>
#include <LiarRefrence.h>
#include <LiarShader.h>

namespace Liar
{
	// ====================  Œ∆¿Ì ================

	class LiarTexture :public LiarReference
	{
	public:
		LiarTexture();
		~LiarTexture();

	private:
		int m_textureType;
		std::string m_path;

	public:
		void SetPath(const char* v) { m_path = v; };
		void SetPath(const std::string& v) { m_path = v; };

		std::string& GetPath() { return m_path; };

		void SetType(int v) { m_textureType = v; };
		int GetType() const { return m_textureType; };

		void Render(Liar::LiarShaderProgram&, size_t);

	private:
		unsigned int m_textureId;

	public:
		void Upload(const char*);
		void Upload(const std::string&);

		unsigned int GetTextureId() const { return m_textureId; };
	};

	// ====================  Œ∆¿Ì ================

	class LiarMaterial
	{
	public:
		LiarMaterial();
		~LiarMaterial();

	private:
		std::vector<Liar::LiarTexture*>* m_allTextures;
		std::string m_type;

		float m_shineness;

	public:
		void EraseIndex(int);

		std::vector<Liar::LiarTexture*>* GetTextures() { return m_allTextures; };
		Liar::LiarTexture* GetTexture(int index) { return m_allTextures->at(index); };

		size_t GetTexSize() { return m_allTextures ? m_allTextures->size() : 0; };

		std::string& GetType() { return m_type; };

		float GetShineness() const { return m_shineness; };

	public:
		void Render(Liar::LiarShaderProgram&);

	};
}

