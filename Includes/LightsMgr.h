#pragma once

#include <LiarLight.h>
#include <LiarShader.h>
#include <vector>

namespace Liar
{
	class LightsMgr
	{
	public:
		LightsMgr();
		~LightsMgr();

	private:
		Liar::LiarDirectionLight* m_dirLight;
		std::vector<Liar::LiarPointLight*>* m_pointLights;
		std::vector<Liar::LiarSpotLight*>* m_spotLights;

	public:
		void Render(Liar::LiarShaderProgram&);

		LiarPointLight* GetPointLight(size_t);
		LiarSpotLight* GetSpotLight(size_t);
		Liar::LiarDirectionLight* GetDirLight() { return m_dirLight; };

	private:
		void Init();
	};
}
