
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <glm.hpp>

namespace Liar
{
	enum COMPONENT_TYPE
	{
		POSITION = 1,
		ROTATION = 2,
		SCALE = 3
	};

	class BaseComponent
	{
	public:
		BaseComponent(COMPONENT_TYPE type = COMPONENT_TYPE::POSITION) :m_type(type), m_val(glm::vec3(0.0f, 0.0f, 0.0f)) {};
		BaseComponent(glm::vec3 val, COMPONENT_TYPE type = COMPONENT_TYPE::POSITION) :m_val(val), m_type(type) {};
		BaseComponent(float x = 0.0f, float y = 0.0f, float z = 0.0f, COMPONENT_TYPE type = COMPONENT_TYPE::POSITION) :m_val(glm::vec3(x, y, z)), m_type(type) {};

	protected:
		glm::vec3 m_val;
		COMPONENT_TYPE m_type;

	public:
		bool SetValue(const glm::vec3&);
		bool SetValue(float, float, float);

		void GetValue(glm::vec3&);
		glm::vec3& GetValue();

		float GetX() const { return m_val.x; };
		float GetY() const { return m_val.y; };
		float GetZ() const { return m_val.z; };
	};

	class CPosition :
		public BaseComponent
	{
	public:
		CPosition() :BaseComponent(COMPONENT_TYPE::POSITION) {};
		CPosition(glm::vec3 val) :BaseComponent(val, COMPONENT_TYPE::POSITION) {};
		CPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f) :BaseComponent(x, y, z, COMPONENT_TYPE::POSITION) {};
	};

	class CRotation :
		public BaseComponent
	{
	public:
		CRotation() :BaseComponent(COMPONENT_TYPE::ROTATION) {};
		CRotation(glm::vec3 val) :BaseComponent(val, COMPONENT_TYPE::ROTATION) {};
		CRotation(float x = 0.0f, float y = 0.0f, float z = 0.0f) :BaseComponent(x, y, z, COMPONENT_TYPE::ROTATION) {};
	};

	class CScale :
		public BaseComponent
	{
		CScale() :BaseComponent(glm::vec3(1.0f, 1.0f, 1.0f), COMPONENT_TYPE::SCALE) {};
		CScale(glm::vec3 val) :BaseComponent(val, COMPONENT_TYPE::SCALE) {};
		CScale(float x = 1.0f, float y = 1.0f, float z = 1.0f) :BaseComponent(x, y, z, COMPONENT_TYPE::SCALE) {};
	};
}

#endif /* COMPONENT_HPP */