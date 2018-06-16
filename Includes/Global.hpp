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
    };
}

#endif /* Global_hpp */
