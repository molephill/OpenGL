#pragma once

namespace Liar
{
	class Camera3D;
	class LiarShaderProgram;
	class LiarBaseShadowMap;

	class ILiarRenderParameter
	{
	public:
		virtual Liar::Camera3D* GetMainCamera() = 0;
		virtual Liar::LiarShaderProgram* GetRootShaderProgram() = 0;
		virtual Liar::LiarBaseShadowMap* GetShadowMap() = 0;
	};

	class ILiarRender
	{
	public:
		virtual bool Render(Liar::ILiarRenderParameter*, bool combineParent = false) = 0;
	};
}