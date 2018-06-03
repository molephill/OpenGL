#version 410 core
out vec4 FragColor;

in vec3 ourColor;

uniform float greenChange;

void main()
{
    FragColor = vec4(ourColor.x, greenChange, ourColor.z, 1.0f);
}
