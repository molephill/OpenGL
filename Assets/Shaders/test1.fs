#version 410 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TextCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
    FragColor = texture(texture0, TextCoord);
}
