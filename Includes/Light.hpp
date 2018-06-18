//
//  Light.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/17.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include <stdio.h>
#include "LiarObject.hpp"

namespace Liar
{
    class Light:public LiarObject
    {
    public:
        Light();
        ~Light();
        
    public:
        virtual void Render(Camera* camera);
        // show
#ifdef DEBUG
        void SetBuffers(unsigned int);
#endif
    };
}

#endif /* Light_hpp */
