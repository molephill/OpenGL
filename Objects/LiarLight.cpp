#include "LiarLight.h"

namespace Liar
{
	LiarDirectionLight::LiarDirectionLight() :Liar::LiarBaseLight()
		, m_direction(new Liar::Vector3D())
	{

	}

	LiarDirectionLight::~LiarDirectionLight()
	{
		delete m_direction;
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

	LiarSpotLight::LiarSpotLight() :Liar::LiarBaseLight()
		, m_direction(new Liar::Vector3D())
		, m_cutoff(0.0f)
	{

	}

	LiarSpotLight::~LiarSpotLight()
	{
		delete m_direction;
	}
}
