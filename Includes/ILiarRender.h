#pragma once

#include <LiarLight.h>
#include <Camera3D.h>
#include <LiarShader.h>

namespace Liar
{
	class ILiarRender
	{
	public:
		virtual void Render(Liar::LiarShaderProgram&, Liar::Camera3D* camera = nullptr, Liar::LiarBaseLight* light = nullptr) = 0;
	};
}