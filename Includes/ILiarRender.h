#pragma once

#include <LiarShader.h>


namespace Liar
{
	class ILiarRender
	{
		virtual void Render(Liar::LiarShaderProgram&) {};
	};
}