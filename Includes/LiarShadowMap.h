#pragma once

#include <Define.h>
#include <LiarShader.h>
#include <Camera3D.h>

#include <glad/glad.h>

#include <vector>

namespace Liar
{
	class LiarBaseShadowMap :public Liar::LiarDisplayObject
	{
	public:
		LiarBaseShadowMap();
		virtual ~LiarBaseShadowMap();

	protected:
		Liar::uint m_width;
		Liar::uint m_height;

		Liar::Vector3D* m_lightPosition;
		Liar::Vector3D* m_lightDirection;
		bool m_lightTransformChanged;
		Liar::Matrix4* m_lightViewTransform;
		Liar::LiarShaderProgram* m_shaderProgram;

	public:
		void SetLightPosition(float, float, float);
		void SetLightPosition(const Liar::Vector3D&);
		void SetLightDirection(float, float, float);
		void SetLightDirection(const Liar::Vector3D&);

		virtual bool Render(const Liar::Camera3D&);
	};

	class LiarShadowMap:public Liar::LiarBaseShadowMap
	{
	public:
		LiarShadowMap();
		~LiarShadowMap();

	private:
		Liar::uint m_mapCount;

		Liar::uint m_frameBuffer;
		std::vector<Liar::uint>* m_shadowMaps;

	public:
		void SetSize(Liar::uint, Liar::uint);
		void BindForWriting(size_t cascadeIndex = 0);
		void BindForReading();

	private:
		void Init();
		void CreateSub();
		void ReleaseSub();
	};

	class LiarCubeShadowMap
	{
	public:
		LiarCubeShadowMap();
		~LiarCubeShadowMap();

	private:
		Liar::uint m_width;
		Liar::uint m_height;
		Liar::uint m_frameBuffer;
		Liar::uint m_shadowMap;
		Liar::uint m_depth;

		Liar::LiarShaderProgram* m_shaderProgram;

	private:
		void Init();
		void CreateSub();
		void ReleaseSub();

	public:
		void BindForWriting(GLenum);
		void BindForReading(GLenum);
	};
}
