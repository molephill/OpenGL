
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
		BaseComponent(COMPONENT_TYPE type = COMPONENT_TYPE::POSITION) :
            m_type(type), m_val(glm::vec3(0.0f, 0.0f, 0.0f)) {};
		BaseComponent(const glm::vec3& val, COMPONENT_TYPE type = COMPONENT_TYPE::POSITION) :
            m_val(val), m_type(type) {};
		BaseComponent(float x = 0.0f, float y = 0.0f, float z = 0.0f,
                      COMPONENT_TYPE type = COMPONENT_TYPE::POSITION) :
            m_val(glm::vec3(x, y, z)), m_type(type) {};

	protected:
		glm::vec3 m_val;
		COMPONENT_TYPE m_type;

	public:
		bool SetValue(const glm::vec3&);
		bool SetValue(float, float, float);
        bool AddValue(const glm::vec3&);
        bool AddValue(float, float, float);

		void GetValue(glm::vec3&);
		glm::vec3& GetValue();

		float GetX() const { return m_val.x; };
		float GetY() const { return m_val.y; };
		float GetZ() const { return m_val.z; };
        
        COMPONENT_TYPE GetType() { return m_type; };
	};

	class CPosition :
		public BaseComponent
	{
	public:
		CPosition() :BaseComponent(COMPONENT_TYPE::POSITION) {};
		CPosition(const glm::vec3& val) :BaseComponent(val, COMPONENT_TYPE::POSITION) {};
		CPosition(float x, float y, float z) :BaseComponent(x, y, z, COMPONENT_TYPE::POSITION) {};
	};

	class CRotation :
		public BaseComponent
	{
	public:
		CRotation() :BaseComponent(COMPONENT_TYPE::ROTATION) {};
		CRotation(const glm::vec3& val) :BaseComponent(val, COMPONENT_TYPE::ROTATION) {};
		CRotation(float x, float y, float z) :BaseComponent(x, y, z, COMPONENT_TYPE::ROTATION) {};
	};

	class CScale :
		public BaseComponent
	{
    public:
		CScale() :BaseComponent(1.0f, 1.0f, 1.0f, COMPONENT_TYPE::SCALE) {};
		CScale(const glm::vec3& val) :BaseComponent(val, COMPONENT_TYPE::SCALE) {};
		CScale(float x, float y, float z) :BaseComponent(x, y, z, COMPONENT_TYPE::SCALE) {};
	};
}

#endif /* COMPONENT_HPP */
