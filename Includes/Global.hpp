//
//  Global.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/16.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Global_hpp
#define Global_hpp

#include <stdio.h>
#include <glm.hpp>

namespace Liar
{
    class WindowActiveMgr;
    class Stage;
    
    class Global
    {
    public:
        static float delataTime;
        static float lastFrame;
        
        static float cameraMoveSpeed;
        static float mouseSensitivity;
        
        static WindowActiveMgr* windowActive;
        static Stage* mainStage;

		static glm::vec3 commonVec3;

	public:
		static void SetVecX(float);
		static void SetVecY(float);
		static void SetVecZ(float);
    };
}

#endif /* Global_hpp */
