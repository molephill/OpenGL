#version 410 core
layout (location = 0) in vec3 aPos;

out vec3 OurColor;

uniform mat4 model;
uniform mat4 viewMatrix;
uniform mat4 projection;
uniform mat4 viewExtentionMatrix;
uniform vec3 color;

void main()
{
    gl_Position = projection * viewMatrix * viewExtentionMatrix * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    OurColor = color;
}