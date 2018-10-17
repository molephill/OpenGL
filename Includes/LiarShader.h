#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <Matrices.h>
#include <Vectors.h>

#include <LiarRefrence.h>

namespace Liar
{
	enum LiarShaderType
	{
		SHADER_TYPE_VERTEXT = 0,
		SHADER_TYPE_FRAGMENT = 1,
		SHADER_TYPE_PROGROM = 2,
	};

	class LiarBaseShader
	{
	public:
		LiarBaseShader();
		~LiarBaseShader();

	public:
		std::string Load(const char*);
	};

	class LiarShaderProgram:public LiarReference
	{
	public:
		LiarShaderProgram();
		~LiarShaderProgram();

	private:
		unsigned int m_programId;

	public:
		void Load(const char*, const char*);
		unsigned int GetProgramId() { return m_programId; };

		void Use();
		// ------------------------------------------------------------------------
		void SetBool(const std::string&, bool value) const;
		// ------------------------------------------------------------------------
		void SetInt(const std::string&, int value) const;
		// ------------------------------------------------------------------------
		void SetFloat(const std::string&, float value) const;
		// ------------------------------------------------------------------------
		void SetVec2(const std::string&, const Liar::Vector2D&) const;
		void SetVec2(const std::string&, float, float) const;
		// ------------------------------------------------------------------------
		void SetVec3(const std::string&, const Liar::Vector3D&) const;
		void SetVec3(const std::string&, float, float, float) const;
		// ------------------------------------------------------------------------
		void SetVec4(const std::string&, const Liar::Vector4D&) const;
		void SetVec4(const std::string&, float, float, float, float) const;
		// ------------------------------------------------------------------------
		void SetMat2(const std::string&, const Liar::Matrix2&) const;
		// ------------------------------------------------------------------------
		void SetMat3(const std::string&, const Liar::Matrix3&) const;
		// ------------------------------------------------------------------------
		void SetMat4(const std::string&, const Liar::Matrix4&) const;

	private:
		void CheckCompileErrors(unsigned int, LiarShaderType);
		void LinkProgram(const char*, const char*);
	};
}

