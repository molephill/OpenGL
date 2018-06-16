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
    float Global::delataTime = 0.0f;
    float Global::lastFrame = 0.0f;
    
    float Global::mouseSensitivity = 0.05f;
    float Global::cameraMoveSpeed = 0.5f;
    
    WindowActiveMgr* Global::windowActive = nullptr;
    Stage* Global::mainStage = nullptr;
}
