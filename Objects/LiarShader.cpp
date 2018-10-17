#include "LiarShader.h"
#include <AssetsMgr.hpp>

namespace Liar
{
	LiarBaseShader::LiarBaseShader()
	{

	}

	LiarBaseShader::~LiarBaseShader()
	{

	}

	std::string LiarBaseShader::Load(const char* path)
	{
		std::ifstream shaderFile;
		shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			shaderFile.open(path);
			std::stringstream shaderStream;
			// read file's buffer contents into streams
			shaderStream << shaderFile.rdbuf();
			// close file handlers
			shaderFile.close();
			// convert stream into string
			return shaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			return "";
		}
	}

	LiarShaderProgram::LiarShaderProgram():
		Liar::LiarReference(),
		m_programId(0)
	{

	}

	LiarShaderProgram::~LiarShaderProgram()
	{
		if (m_programId > 0)
		{
			glDeleteProgram(m_programId);
		}
	}

	void LiarShaderProgram::Load(const char* vertexFile, const char* fragmentFile)
	{
		std::string vertex = AssetsMgr::GetInstance().GetBaseShaderCode(vertexFile);
		std::string fragment = AssetsMgr::GetInstance().GetBaseShaderCode(fragmentFile);
		LinkProgram(vertex.c_str(), fragment.c_str());
	}

	void LiarShaderProgram::LinkProgram(const char* vShaderCode, const char * fShaderCode)
	{
		// 2. compile shaders
		unsigned int vertex, fragment;

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CheckCompileErrors(vertex, LiarShaderType::SHADER_TYPE_VERTEXT);

		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CheckCompileErrors(fragment, LiarShaderType::SHADER_TYPE_FRAGMENT);

		// shader Program
		m_programId = glCreateProgram();
		glAttachShader(m_programId, vertex);
		glAttachShader(m_programId, fragment);
		glLinkProgram(m_programId);
		CheckCompileErrors(m_programId, LiarShaderType::SHADER_TYPE_PROGROM);

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	// ¼ì²â±¨´í
	void LiarShaderProgram::CheckCompileErrors(unsigned int shader, LiarShaderType type)
	{
		int success;
		char infoLog[DEFAULT_BUFF_SIZE];
		if (type != LiarShaderType::SHADER_TYPE_PROGROM)
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, DEFAULT_BUFF_SIZE, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, DEFAULT_BUFF_SIZE, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}

	void LiarShaderProgram::Use()
	{
		glUseProgram(m_programId);
	}

	// utility uniform functions
	// ------------------------------------------------------------------------
	void LiarShaderProgram::SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
	}

	// ------------------------------------------------------------------------
	void LiarShaderProgram::SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_programId, name.c_str()), static_cast<int>(value));
	}
	// ------------------------------------------------------------------------

	void LiarShaderProgram::SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
	}

	// ------------------------------------------------------------------------
	void LiarShaderProgram::SetVec2(const std::string& name, const Liar::Vector2D& value) const
	{
		SetVec2(name, value.x, value.y);
	}
	void LiarShaderProgram::SetVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(m_programId, name.c_str()), x, y);
	}

	// ------------------------------------------------------------------------
	void LiarShaderProgram::SetVec3(const std::string& name, const Liar::Vector3D& value) const
	{
		SetVec3(name, value.x, value.y, value.z);
	}
	void LiarShaderProgram::SetVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(m_programId, name.c_str()), x, y, z);
	}

	// ------------------------------------------------------------------------
	void LiarShaderProgram::SetVec4(const std::string& name, const Liar::Vector4D& value) const
	{
		SetVec4(name, value.x, value.y, value.z, value.w);
	}
	void LiarShaderProgram::SetVec4(const std::string& name, float x, float y, float z, float w) const
	{
		glUniform4f(glGetUniformLocation(m_programId, name.c_str()), x, y, z, w);
	}

	// ------------------------------------------------------------------------
	void LiarShaderProgram::SetMat2(const std::string& name, const Liar::Matrix2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, mat.Get());
	}

	// ------------------------------------------------------------------------
	void LiarShaderProgram::SetMat3(const std::string& name, const Liar::Matrix3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, mat.Get());
	}

	// ------------------------------------------------------------------------
	void LiarShaderProgram::SetMat4(const std::string&name, const Liar::Matrix4& m) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, m.Get());
	}

}
