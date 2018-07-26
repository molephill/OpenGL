#include <Global.hpp>

namespace Liar
{
	float Global::delataTime = 0.0f;
	float Global::lastFrame = 0.0f;

	float Global::cameraMoveSpeed = 0.0f;
	float Global::mouseSensitivity = 0.0f;

	WindowActiveMgr* Global::windowActive = nullptr;
	Stage* Global::mainStage = nullptr;
}