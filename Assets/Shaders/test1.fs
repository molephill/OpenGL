#version 410 core
out vec4 FragColor;

uniform sampler2D texture;
in vec2 TexCoords;

in vec3 ourColor;
void main()
{
    //FragColor = vec4(ourColor, 1.0f);
    FragColor = texture(texture, TexCoords);
}
