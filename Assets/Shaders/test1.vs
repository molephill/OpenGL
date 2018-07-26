#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec3 aUV;

out vec3 ourColor;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(aPos, 1.0);
    ourColor = aColor;
}
