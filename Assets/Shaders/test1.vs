#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aUV;
layout (location = 3) in vec3 aColor;

out vec3 ourColor;
out vec2 TextCoord;

uniform mat4 projection;
uniform mat4 viewMatrix;
uniform mat4 model;

void main()
{
    gl_Position = projection * viewMatrix * model * vec4(aPos, 1.0);
    //gl_Position = projection * vec4(aPos, 1.0);
    ourColor = aColor;
    TextCoord = vec2(aUV.x, aUV.y);
}
