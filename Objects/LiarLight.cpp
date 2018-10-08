#include "LiarLight.h"
#include <AssetsMgr.hpp>

namespace Liar
{
    LiarBaseLight::LiarBaseLight():
        Liar::LiarDisplayObject(),
        m_shader(nullptr),
        m_color(new Liar::Vector3D(1.0f, 1.0f, 1.0f)),
        m_ambient(new Liar::Vector3D()),
        m_diffuse(new Liar::Vector3D()),
        m_specular(new Liar::Vector3D())
    {
//        m_shader = AssetsMgr::GetInstance().GetShaderProgrom("base",
//                                                             AssetsMgr::GetPath("Shaders/base/base.vs"), AssetsMgr::GetPath("Shaders/base/base.vs"));
    }
    
	LiarBaseLight::~LiarBaseLight()
	{
		delete m_color;
		if (m_shader)
		{
			AssetsMgr::GetInstance().ReleaseShaderProgram(m_shader);
		}
	}

	void LiarBaseLight::BuildProgram(Liar::LiarShaderProgram& shader, std::string base)
	{
		shader.SetVec3(base + "baseLight.color", *m_color);
		shader.SetVec3(base + "baseLight.ambient", *m_ambient);
		shader.SetVec3(base + "baseLight.diffuse", *m_diffuse);
		shader.SetVec3(base + "baseLight.specular", *m_specular);
	}

	void LiarBaseLight::Render(const Liar::Camera3D& camera, Liar::LiarShaderProgram& shader, int)
	{
        Liar::LiarDisplayObject::Render(shader);
		BuildProgram(shader);
        if(m_shader)
        {
            m_shader->Use();
            m_shader->SetMat4("projection", *(camera.GetProjMatrix()));
            m_shader->SetMat4("viewMatrix", *(camera.GetTransform()));
            m_shader->SetMat4("viewExtentionMatrix", *(camera.GetExtentionMatrix()));
            m_shader->SetVec3("color", *m_color);
        }
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
		, m_direction(new Liar::Vector3D(1.0, 0, 0))
	{
	}

	LiarDirectionLight::~LiarDirectionLight()
	{
		delete m_direction;
	}

	void LiarDirectionLight::BuildProgram(Liar::LiarShaderProgram& shader, std::string)
	{
		Liar::LiarBaseLight::BuildProgram(shader, "dirLight.");
		shader.SetVec3("dirLight.direction", *m_direction);
	}

	LiarPointLight::LiarPointLight() :Liar::LiarBaseLight()
		, m_constant(1.0f), m_linear(0.0f), m_quadratic(0.0f)
	{

	}

	LiarPointLight::~LiarPointLight()
	{
	}

	void LiarPointLight::BuildProgram(Liar::LiarShaderProgram& shader, std::string base)
	{
		Liar::LiarBaseLight::BuildProgram(shader, base);

		shader.SetVec3(base + "position", *m_position);
		shader.SetFloat(base + "constant", m_constant);
		shader.SetFloat(base + "linear", m_linear);
		shader.SetFloat(base + "quadratic", m_quadratic);
	}

	void LiarPointLight::Render(const Liar::Camera3D& camera, Liar::LiarShaderProgram& shader, int index)
	{
		char name[128];
		memset(name, 0, sizeof(name));
		snprintf(name, sizeof(name), "pointLights[%d].", index);
		std::string base(name);

		BuildProgram(shader, base);
        LiarBaseLight::Render(camera, shader, index);
	}

	LiarSpotLight::LiarSpotLight() :Liar::LiarPointLight()
		, m_direction(new Liar::Vector3D())
		, m_cutOff(0.0f)
	{

	}

	LiarSpotLight::~LiarSpotLight()
	{
		delete m_direction;
	}

	void LiarSpotLight::Render(const Liar::Camera3D& camera, Liar::LiarShaderProgram& shader, int index)
	{
		char name[128];
		memset(name, 0, sizeof(name));
		snprintf(name, sizeof(name), "spotLights[%d].", index);
		std::string base(name);
		Liar::LiarPointLight::BuildProgram(shader, base + "pointLight.");

		shader.SetVec3(base + "direction", *m_direction);
		shader.SetFloat(base + "cutOff", m_cutOff);
		shader.SetFloat(base + "outerCutOff", m_outerCutOff);
        LiarBaseLight::Render(camera, shader, index);
	}
}
