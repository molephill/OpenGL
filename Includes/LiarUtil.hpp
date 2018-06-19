//
//  LiarUtil.hpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/16.
//  Copyright © 2018年 lier. All rights reserved.
//

#ifndef LiarUtil_hpp
#define LiarUtil_hpp

#include <stdio.h>

#include <glm.hpp>
#include "Component.hpp"

namespace Liar
{
    class LiarUtil
    {
    public:
        static glm::mat4 LookAt(const glm::vec3&, const glm::vec3&, const glm::vec3&);
		static void RestMatrix(glm::mat4&);
    };
}

#endif /* LiarUtil_hpp */
