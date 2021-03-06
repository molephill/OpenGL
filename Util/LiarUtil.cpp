//
//  LiarUtil.cpp
//  OpenGL
//
//  Created by 毛伟 on 2018/6/16.
//  Copyright © 2018年 lier. All rights reserved.
//

#include "LiarUtil.hpp"

namespace Liar
{
    glm::mat4 LiarUtil::LookAt(const glm::vec3& position, const glm::vec3& target, const glm::vec3& worldUp)
    {
        // 1. Position = known
        // 2. Calculate cameraDirection
        glm::vec3 zaxis = glm::normalize(position - target);
        // 3. Get positive right axis vector
        glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
        // 4. Calculate camera up vector
        glm::vec3 yaxis = glm::cross(zaxis, xaxis);
        
        // Create translation and rotation matrix
        // In glm we access elements as mat[col][row] due to column-major layout
        glm::mat4 translation(1.0f); // Identity matrix by default
        translation[3][0] = -position.x; // Third column, first row
        translation[3][1] = -position.y;
        translation[3][2] = -position.z;
        glm::mat4 rotation(1.0f);
        rotation[0][0] = xaxis.x; // First column, first row
        rotation[1][0] = xaxis.y;
        rotation[2][0] = xaxis.z;
        rotation[0][1] = yaxis.x; // First column, second row
        rotation[1][1] = yaxis.y;
        rotation[2][1] = yaxis.z;
        rotation[0][2] = zaxis.x; // First column, third row
        rotation[1][2] = zaxis.y;
        rotation[2][2] = zaxis.z;
        
        // Return lookAt matrix as combination of translation and rotation matrix
        return rotation * translation; // Remember to read from right to left (first translation then rotation)
    }

	// reset
	void LiarUtil::RestMatrix(glm::mat4& matrix)
	{
		matrix[0][0] = 1.0f;
		matrix[0][1] = 0.0f;
		matrix[0][2] = 0.0f;
		matrix[0][3] = 0.0f;

		matrix[1][0] = 0.0f;
		matrix[1][1] = 1.0f;
		matrix[1][2] = 0.0f;
		matrix[1][3] = 0.0f;

		matrix[2][0] = 0.0f;
		matrix[2][1] = 0.0f;
		matrix[2][2] = 1.0f;
		matrix[2][3] = 0.0f;

		matrix[3][0] = 0.0f;
		matrix[3][1] = 0.0f;
		matrix[3][2] = 0.0f;
		matrix[3][3] = 1.0f;
	}
}
