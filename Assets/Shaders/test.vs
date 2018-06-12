#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

//uniform float xOffset;

uniform mat4 aTransform;
uniform mat4 projection;

void main()
{
//    gl_Position = vec4(aPos.x+xOffset, aPos.y, aPos.z, 1.0); // just add a - to the y position
    gl_Position = projection * aTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, -aTexCoord.y);
}
