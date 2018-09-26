#pragma once

#include <Vectors.h>

namespace Liar
{
	class LiarBaseLight
	{
	public:
		LiarBaseLight() :m_color(new Liar::Vector3D(1.0f, 1.0f, 1.0f)), m_ambient(0.0f), m_diffuse(0.0f) {};
		~LiarBaseLight() 
		{
			delete m_color;
		};

	protected:
		Liar::Vector3D* m_color;
		float m_ambient;
		float m_diffuse;

	public:
		void SetColor(float x, float y, float z) { m_color->Set(x, y, z); };
		void SetColor(const Liar::Vector3D& rhs) { m_color->Set(rhs); };
		void SetAmbient(float v) { m_ambient = v; };
		void SetDiffuse(float v) { m_diffuse = v; };

		Liar::Vector3D* GetColor() const { return m_color; };
		float GetAmbient() const { return m_ambient; };
		float GetDiffuse() const { return m_diffuse; };
	};

	class LiarDirectionLight :public LiarBaseLight
	{
	public:
		LiarDirectionLight();
		~LiarDirectionLight();

	private:
		Liar::Vector3D* m_direction;

	public:
		void SetDirection(float x, float y, float z) { m_direction->Set(x, y, z); };
		void SetDirection(const Liar::Vector3D& rhs) { m_direction->Set(rhs); };

		Liar::Vector3D* GetDirection() const { return m_direction; };
	};

	class LiarPointLight :public LiarBaseLight
	{
	public:
		LiarPointLight();
		~LiarPointLight();

	private:
		Liar::Vector3D* m_position;
		float m_constant;
		float m_liner;
		float m_exp;

	public:
		void SetPositon(float x, float y, float z) { m_position->Set(x, y, z); };
		void SetPositon(const Liar::Vector3D& rhs) { m_position->Set(rhs); };
		void SetConstant(float v) { m_constant = v; };
		void SetLiner(float v) { m_liner = v; };
		void SetExp(float v) { m_exp = v; };

		Liar::Vector3D* GetPosition() const { return m_position; };
		float GetConstant() const { return m_constant; };
		float GetLiner() const { return m_liner; };
		float GetExp() const { return m_exp; };
	};

	class LiarSpotLight :public LiarBaseLight
	{
	public:
		LiarSpotLight();
		~LiarSpotLight();

	private:
		Liar::Vector3D* m_direction;
		float m_cutoff;

	public:
		void SetDirection(float x, float y, float z) { m_direction->Set(x, y, z); };
		void SetDirection(const Liar::Vector3D& rhs) { m_direction->Set(rhs); };
		void SetCutoff(float v) { m_cutoff = v; };

		Liar::Vector3D* GetDirection() const { return m_direction; };
		float GetCutoff() const { return m_cutoff; };
	};
}

