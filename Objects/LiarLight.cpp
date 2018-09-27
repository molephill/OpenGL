#include "LiarLight.h"
#include <AssetsMgr.hpp>

namespace Liar
{
	LiarBaseLight::~LiarBaseLight()
	{
		delete m_color;
		if (m_shader)
		{
			AssetsMgr::GetInstance().ReleaseShaderProgram(m_shader);
		}
	}

	void LiarBaseLight::SetProgram(Liar::LiarShaderProgram& shader, std::string base)
	{
		shader.SetVec3(base + "baseLight.color", *m_color);
		shader.SetFloat(base + "baseLight.ambient", m_ambient);
		shader.SetFloat(base + "baseLight.diffuse", m_diffuse);
	}

	void LiarBaseLight::Render(Liar::LiarShaderProgram& shader, int)
	{
		SetProgram(shader);
	}

	void LiarBaseLight::Render(int index)
	{
		Render(*m_shader, index);
	}

	void LiarBaseLight::SetProgram(const char* name, const char* vertexFile, const char* fragmentFile)
	{
		m_shader = AssetsMgr::GetInstance().GetShaderProgrom(name, vertexFile, fragmentFile);
	}

	void LiarBaseLight::SetProgram(const std::string& name, const std::string& vertexFile, const std::string& fragementFile)
	{
		SetProgram(name.c_str(), vertexFile.c_str(), fragementFile.c_str());
	}

	LiarDirectionLight::LiarDirectionLight() :Liar::LiarBaseLight()
		, m_position(new Liar::Vector3D(1.0, 0, 0))
	{

	}

	LiarDirectionLight::~LiarDirectionLight()
	{
		delete m_position;
	}

	void LiarDirectionLight::SetProgram(Liar::LiarShaderProgram& shader, std::string)
	{
		Liar::LiarBaseLight::SetProgram(shader, "directionalLight.");
		shader.SetVec3("directionalLight.position", *m_position);
	}

	LiarPointLight::LiarPointLight() :Liar::LiarBaseLight()
		, m_position(new Liar::Vector3D())
		, m_constant(1.0f), m_liner(0.0f), m_exp(0.0f)
	{

	}

	LiarPointLight::~LiarPointLight()
	{
		delete m_position;
	}

	void LiarPointLight::SetProgram(Liar::LiarShaderProgram& shader, std::string base)
	{
		Liar::LiarBaseLight::SetProgram(shader, base);

		shader.SetVec3(base + "Position", *m_position);
		shader.SetFloat(base + "Constant", m_constant);
		shader.SetFloat(base + "Linear", m_liner);
		shader.SetFloat(base + "Exp", m_exp);
	}

	void LiarPointLight::Render(Liar::LiarShaderProgram& shader, int index)
	{
		char name[128];
		memset(name, 0, sizeof(name));
		snprintf(name, sizeof(name), "PointLights[%d].", index);
		std::string base(name);

		SetProgram(shader, base);
	}

	LiarSpotLight::LiarSpotLight() :Liar::LiarPointLight()
		, m_direction(new Liar::Vector3D())
		, m_cutoff(0.0f)
	{

	}

	LiarSpotLight::~LiarSpotLight()
	{
		delete m_direction;
	}

	void LiarSpotLight::Render(Liar::LiarShaderProgram& shader, int index)
	{
		char name[128];
		memset(name, 0, sizeof(name));
		snprintf(name, sizeof(name), "SpoitLights[%d].", index);
		std::string base(name);
		Liar::LiarPointLight::SetProgram(shader, base + "Base.");

		shader.SetVec3(base + "Direction", *m_direction);
		shader.SetFloat(base + "Cutoff", m_cutoff);
	}
}
