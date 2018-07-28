#version 410 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 ourColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
    FragColor = texture(texture1, TexCoords);
}
