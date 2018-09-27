#pragma once

#include <Vectors.h>
#include <LiarShader.h>

namespace Liar
{
	class LiarBaseLight
	{
	public:
		LiarBaseLight() :
			m_color(new Liar::Vector3D(1.0f, 1.0f, 1.0f)), 
			m_ambient(new Liar::Vector3D()), 
			m_diffuse(new Liar::Vector3D()),
			m_specular(new Liar::Vector3D()),
			m_shader(nullptr) {};
		~LiarBaseLight();

	protected:
		Liar::Vector3D* m_color;
		Liar::Vector3D* m_ambient;
		Liar::Vector3D* m_diffuse;
		Liar::Vector3D* m_specular;
		Liar::LiarShaderProgram* m_shader;

		virtual void BuildProgram(Liar::LiarShaderProgram&, std::string base = "");

	public:
		void SetColor(float x, float y, float z) { m_color->Set(x, y, z); };
		void SetColor(const Liar::Vector3D& rhs) { m_color->Set(rhs); };
		void SetAmbient(float x, float y, float z) { m_ambient->Set(x, y, z);};
		void SetAmbient(const Liar::Vector3D& rhs) { m_ambient->Set(rhs); };
		void SetDiffuse(float x, float y, float z) { m_diffuse->Set(x, y, z); };
		void SetDiffuse(const Liar::Vector3D& rhs) { m_diffuse->Set(rhs); };
		void SetSpecular(float x, float y, float z) { m_specular->Set(x, y, z); };
		void SetSpecular(const Liar::Vector3D& rhs) { m_specular->Set(rhs); };

		Liar::Vector3D* GetColor() const { return m_color; };
		Liar::Vector3D* GetAmbient() const { return m_ambient; };
		Liar::Vector3D* GetDiffuse() const { return m_diffuse; };
		Liar::Vector3D* GetSpecular() const { return m_specular; };

		void SetProgram(const char*, const char*, const char*);
		void SetProgram(const std::string&, const std::string&, const std::string&);

		Liar::LiarShaderProgram* GetShaderProgram() { return m_shader; };

		virtual void Render(Liar::LiarShaderProgram&, int index = 0);
		virtual void Render(int index = 0);
	};

	class LiarDirectionLight :public LiarBaseLight
	{
	public:
		LiarDirectionLight();
		~LiarDirectionLight();

	private:
		Liar::Vector3D* m_direction;

	protected:
		virtual void BuildProgram(Liar::LiarShaderProgram&, std::string base = "");

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

	protected:
		Liar::Vector3D* m_position;
		float m_constant;
		float m_linear;
		float m_quadratic;

		virtual void BuildProgram(Liar::LiarShaderProgram&, std::string base = "");

	public:
		void SetPositon(float x, float y, float z) { m_position->Set(x, y, z); };
		void SetPositon(const Liar::Vector3D& rhs) { m_position->Set(rhs); };
		void SetConstant(float v) { m_constant = v; };
		void SetLinear(float v) { m_linear = v; };
		void SetQuadratic(float v) { m_quadratic = v; };

		Liar::Vector3D* GetPosition() const { return m_position; };
		float GetConstant() const { return m_constant; };
		float GetLiner() const { return m_linear; };
		float GetQuadratic() const { return m_quadratic; };

		virtual void Render(Liar::LiarShaderProgram&, int index = 0);
	};

	class LiarSpotLight :public LiarPointLight
	{
	public:
		LiarSpotLight();
		~LiarSpotLight();

	private:
		Liar::Vector3D* m_direction;
		float m_cutOff;
		float m_outerCutOff;

	public:
		void SetDirection(float x, float y, float z) { m_direction->Set(x, y, z); };
		void SetDirection(const Liar::Vector3D& rhs) { m_direction->Set(rhs); };
		void SetCutOff(float v) { m_cutOff = v; };
		void SetOuterCutOff(float v) { m_outerCutOff = v; };

		Liar::Vector3D* GetDirection() const { return m_direction; };
		float GetCutoff() const { return m_cutOff; };
		float GetOuterCutOff() const { return m_outerCutOff; };

		virtual void Render(Liar::LiarShaderProgram&, int index = 0);
	};
}

