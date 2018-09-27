#include "LightsMgr.h"

namespace Liar
{
	LightsMgr::LightsMgr():
		m_dirLight(new Liar::LiarDirectionLight()),
		m_pointLights(new std::vector<Liar::LiarPointLight*>()),
		m_spotLights(new std::vector<Liar::LiarSpotLight*>())
	{
		Init();
	}


	LightsMgr::~LightsMgr()
	{
		delete m_dirLight;

		for (std::vector<Liar::LiarPointLight*>::iterator it = m_pointLights->begin(); it < m_pointLights->end();)
		{
			delete *it;
			it = m_pointLights->erase(it);
		}
		std::vector<Liar::LiarPointLight*>().swap(*m_pointLights);
		delete m_pointLights;

		for (std::vector<Liar::LiarSpotLight*>::iterator it = m_spotLights->begin(); it < m_spotLights->end();)
		{
			delete *it;
			it = m_spotLights->erase(it);
		}
		std::vector<Liar::LiarSpotLight*>().swap(*m_spotLights);
		delete m_spotLights;
	}

	void LightsMgr::Init()
	{
		m_dirLight->SetDirection(-0.2f, -1.0f, -0.3f);
		m_dirLight->SetAmbient(0.05f, 0.05f, 0.05f);
		m_dirLight->SetDiffuse(0.4f, 0.4f, 0.4f);
		m_dirLight->SetSpecular(0.5f, 0.5f, 0.5f);

		m_pointLights->push_back(new Liar::LiarPointLight());
		m_pointLights->push_back(new Liar::LiarPointLight());
		m_pointLights->push_back(new Liar::LiarPointLight());
		m_pointLights->push_back(new Liar::LiarPointLight());

		Liar::LiarPointLight* pointLight = m_pointLights->at(0);
		pointLight->SetPositon(0.7f, 0.2f, 2.0f);
		pointLight->SetAmbient(0.05f, 0.05f, 0.05f);
		pointLight->SetDiffuse(0.8f, 0.8f, 0.8f);
		pointLight->SetSpecular(1.0f, 1.0f, 1.0f);
		pointLight->SetConstant(1.0f);
		pointLight->SetLinear(0.09f);
		pointLight->SetQuadratic(0.032f);

		pointLight = m_pointLights->at(1);
		pointLight->SetPositon(2.3f, -3.3f, -4.0f);
		pointLight->SetAmbient(0.05f, 0.05f, 0.05f);
		pointLight->SetDiffuse(0.8f, 0.8f, 0.8f);
		pointLight->SetSpecular(1.0f, 1.0f, 1.0f);
		pointLight->SetConstant(1.0f);
		pointLight->SetLinear(0.09f);
		pointLight->SetQuadratic(0.032f);

		pointLight = m_pointLights->at(2);
		pointLight->SetPositon(-4.0f, 2.0f, -12.0f);
		pointLight->SetAmbient(0.05f, 0.05f, 0.05f);
		pointLight->SetDiffuse(0.8f, 0.8f, 0.8f);
		pointLight->SetSpecular(1.0f, 1.0f, 1.0f);
		pointLight->SetConstant(1.0f);
		pointLight->SetLinear(0.09f);
		pointLight->SetQuadratic(0.032f);

		pointLight = m_pointLights->at(3);
		pointLight->SetPositon(0.0f, 0.0f, -3.0f);
		pointLight->SetAmbient(0.05f, 0.05f, 0.05f);
		pointLight->SetDiffuse(0.8f, 0.8f, 0.8f);
		pointLight->SetSpecular(1.0f, 1.0f, 1.0f);
		pointLight->SetConstant(1.0f);
		pointLight->SetLinear(0.09f);
		pointLight->SetQuadratic(0.032f);

		m_spotLights->push_back(new Liar::LiarSpotLight());
		Liar::LiarSpotLight* spotLight = m_spotLights->at(0);

		spotLight->SetDirection(0, 1, 0);
		spotLight->SetAmbient(0.0f, 0.0f, 0.0f);
		spotLight->SetDiffuse(1.0f, 1.0f, 1.0f);
		spotLight->SetSpecular(1.0f, 1.0f, 1.0f);
		spotLight->SetConstant(1.0f);
		spotLight->SetLinear(0.09f);
		spotLight->SetQuadratic(0.032f);
		spotLight->SetCutOff(0.2f);
		spotLight->SetOuterCutOff(0.23f);
	}

	void LightsMgr::Render(Liar::LiarShaderProgram& shader)
	{
		shader.SetInt("numPointLight", m_pointLights->size());
		shader.SetInt("numSpotLight", m_spotLights->size());
		m_dirLight->Render(shader, 0);
		int index = 0;
		for (std::vector<Liar::LiarPointLight*>::iterator it = m_pointLights->begin(); it < m_pointLights->end(); ++it)
		{
			(*it)->Render(shader, index++);
		}

		index = 0;
		for (std::vector<Liar::LiarSpotLight*>::iterator it = m_spotLights->begin(); it < m_spotLights->end(); ++it)
		{
			(*it)->Render(shader, index++);
		}
	}

	Liar::LiarPointLight* LightsMgr::GetPointLight(size_t index)
	{
		return index >= m_pointLights->size() ? nullptr : m_pointLights->at(index);
	}

	Liar::LiarSpotLight* LightsMgr::GetSpotLight(size_t index)
	{
		return index >= m_spotLights->size() ? nullptr : m_spotLights->at(index);
	}
}