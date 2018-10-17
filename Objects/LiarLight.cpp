#include "LiarLight.h"
#include <AssetsMgr.hpp>

namespace Liar
{
    LiarBaseLight::LiarBaseLight():
        Liar::LiarMesh(),
        m_shaderProgram(nullptr),
        m_color(new Liar::Vector3D(1.0f, 1.0f, 1.0f)),
        m_ambient(new Liar::Vector3D()),
        m_diffuse(new Liar::Vector3D()),
        m_specular(new Liar::Vector3D())
    {
        m_shaderProgram = AssetsMgr::GetInstance().GetShaderProgrom("light_shape",
                  AssetsMgr::GetPath("Shaders/base/base.vs").c_str(), AssetsMgr::GetPath("Shaders/base/base.fs").c_str());
		m_geometry = Liar::LiarPolygonGeoMgr::GetGeo(Liar::LiarPolygonGeometryType::GeometryType_Cube);
    }
    
	LiarBaseLight::~LiarBaseLight()
	{
		delete m_color;
		if (m_shaderProgram)
		{
			AssetsMgr::GetInstance().ReleaseShaderProgram(m_shaderProgram);
		}
		Liar::LiarPolygonGeoMgr::ReleaseGeo(Liar::LiarPolygonGeometryType::GeometryType_Sphere);
		m_geometry = nullptr;
	}

	void LiarBaseLight::BuildProgram(Liar::ILiarRenderParameter* para, const char* baseChar)
	{
		std::string base = baseChar ? baseChar : "";
		para->GetRootShaderProgram()->SetVec3(base + "baseLight.color", *m_color);
		para->GetRootShaderProgram()->SetVec3(base + "baseLight.ambient", *m_ambient);
		para->GetRootShaderProgram()->SetVec3(base + "baseLight.diffuse", *m_diffuse);
		para->GetRootShaderProgram()->SetVec3(base + "baseLight.specular", *m_specular);
	}

	void LiarBaseLight::LightEffect(Liar::ILiarRenderParameter* para, int)
	{
		BuildProgram(para);
	}

	void LiarBaseLight::SetProgram(const char* name, const char* vertexFile, const char* fragmentFile)
	{
		m_shaderProgram = AssetsMgr::GetInstance().GetShaderProgrom(name, vertexFile, fragmentFile);
	}

	void LiarBaseLight::SetProgram(const std::string& name, const std::string& vertexFile, const std::string& fragementFile)
	{
		SetProgram(name.c_str(), vertexFile.c_str(), fragementFile.c_str());
	}

	bool LiarBaseLight::Render(Liar::ILiarRenderParameter* para, bool combineParent)
	{
		if (m_shaderProgram)
		{
			m_shaderProgram->Use();
			m_shaderProgram->SetMat4("projection", *(para->GetMainCamera()->GetProjMatrix()));
			m_shaderProgram->SetMat4("viewMatrix", *(para->GetMainCamera()->GetTransform()));
			m_shaderProgram->SetMat4("viewExtentionMatrix", *(para->GetMainCamera()->GetExtentionMatrix()));
			m_shaderProgram->SetVec3("color", *m_color);

			return Liar::LiarMesh::Render(para, false);
		}
		return false;
	}

	LiarDirectionLight::LiarDirectionLight() :Liar::LiarBaseLight()
		, m_direction(new Liar::Vector3D(1.0, 0, 0))
	{
	}

	LiarDirectionLight::~LiarDirectionLight()
	{
		delete m_direction;
	}

	void LiarDirectionLight::BuildProgram(Liar::ILiarRenderParameter* para, const char*)
	{
		Liar::LiarBaseLight::BuildProgram(para, "dirLight.");
		para->GetRootShaderProgram()->SetVec3("dirLight.direction", *m_direction);
	}

	// =================================== PointLight ====================================
	LiarPointLight::LiarPointLight() :Liar::LiarBaseLight()
		, m_constant(1.0f), m_linear(0.0f), m_quadratic(0.0f)
	{

	}

	LiarPointLight::~LiarPointLight()
	{
	}

	void LiarPointLight::BuildProgram(Liar::ILiarRenderParameter* para, const char* baseChar)
	{
		Liar::LiarBaseLight::BuildProgram(para, baseChar);

		std::string base = baseChar ? baseChar : "";
		para->GetRootShaderProgram()->SetVec3(base + "position", *m_position);
		para->GetRootShaderProgram()->SetFloat(base + "constant", m_constant);
		para->GetRootShaderProgram()->SetFloat(base + "linear", m_linear);
		para->GetRootShaderProgram()->SetFloat(base + "quadratic", m_quadratic);
	}

	void LiarPointLight::LightEffect(Liar::ILiarRenderParameter* para, int index)
	{
		char name[128];
		memset(name, 0, sizeof(name));
		snprintf(name, sizeof(name), "pointLights[%d].", index);
		std::string base(name);

		BuildProgram(para, base.c_str());
        LiarBaseLight::LightEffect(para, index);
	}

	// =================================== SpotLight ====================================
	LiarSpotLight::LiarSpotLight() :Liar::LiarPointLight()
		, m_direction(new Liar::Vector3D())
		, m_cutOff(0.0f)
	{

	}

	LiarSpotLight::~LiarSpotLight()
	{
		delete m_direction;
	}

	void LiarSpotLight::SetDirection(float x, float y, float z)
	{
		if (!m_direction->Equal(x, y, z))
		{
			m_direction->Set(x, y, z);
			m_direction->Normalize();
		}
	}

	void LiarSpotLight::SetDirection(const Liar::Vector3D& rhs)
	{
		SetDirection(rhs.x, rhs.y, rhs.z);
	}

	void LiarSpotLight::LightEffect(Liar::ILiarRenderParameter* para, int index)
	{
		char name[128];
		memset(name, 0, sizeof(name));
		snprintf(name, sizeof(name), "spotLights[%d].", index);
		std::string base(name);
		std::string tmpBase = base + "pointLight.";
		Liar::LiarPointLight::BuildProgram(para, tmpBase.c_str());

		para->GetRootShaderProgram()->SetVec3(base + "direction", *m_direction);
		para->GetRootShaderProgram()->SetFloat(base + "cutOff", m_cutOff);
		para->GetRootShaderProgram()->SetFloat(base + "outerCutOff", m_outerCutOff);
        LiarBaseLight::LightEffect(para, index);
	}
}
