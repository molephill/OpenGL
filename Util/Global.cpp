//
//  Global.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/16.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "Global.hpp"
#include "Stage.hpp"

namespace Liar
{
	void Global::SetVecX(float x)
	{
		Global::commonVec3.x = x;
		Global::commonVec3.y = 0.0f;
		Global::commonVec3.z = 0.0f;
	}

	void Global::SetVecY(float y)
	{
		Global::commonVec3.x = 0.0f;
		Global::commonVec3.y = y;
		Global::commonVec3.z = 0.0f;
	}

	void Global::SetVecZ(float z)
	{
		Global::commonVec3.x = 0.0f;
		Global::commonVec3.y = 0.0f;
		Global::commonVec3.z = z;
	}

    float Global::delataTime = 0.0f;
    float Global::lastFrame = 0.0f;
    
    float Global::mouseSensitivity = 0.1f;
    float Global::cameraMoveSpeed = 0.5f;

	glm::vec3 Global::commonVec3 = glm::vec3(1.0f);
    
    WindowActiveMgr* Global::windowActive = nullptr;
    Stage* Global::mainStage = nullptr;
}
